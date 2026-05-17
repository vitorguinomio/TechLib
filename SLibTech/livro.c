#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "livro.h"
#include "emprestimo.h"
#include "leitor.h"
#include "utils.h"

#define RESET_CURSOR "\033[H"

Livro livros[MAX_LIVROS] = {
    // {id, titulo, autor, Editora, edicao(ano), disponivel, estado}
    {1, "Alice no pais das maravilhas", "Lewis Carroll", "Panini", 2010, 1, DISPONIVEL},
    {2, "Sense Life", "Glitch Tellend", "Independente", 2021, 1, DISPONIVEL},
    {3, "Depressao para leigos", "John Preston", "Alta Books", 2012, 1, DISPONIVEL},
    {4, "A sutil arte de ligar o foda-se", "Mark Manson", "Intrinseca", 2017, 1, DISPONIVEL},
    {5, "Chapeuzinho vermelho", "Charles Perrault", "Ciranda Cultural", 1995, 1, DISPONIVEL}
};

int totalLivros = 5;

Livro *buscarLivroPorId(int id) {
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id == id) return &livros[i];
    }
    return NULL;
}

int gerar_id_Livro() {
    int max_id = 0;
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id > max_id) {
            max_id = livros[i].id;
        }
    }
    return max_id + 1;
}

int verificar_ano(){
    char entrada[20];
    int ano = 0;
    int valido = 0;

    while (!valido) {
        printf("Digite o ano de edição do livro (4 digitos): ");
        
        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = 0;

            if (strlen(entrada) == 4) {
                valido = 1;
                
                for (int i = 0; i < 4; i++) {
                    if (!isdigit(entrada[i])) {
                        valido = 0;
                        break;
                    }
                }

                if (valido) {
                    ano = atoi(entrada);
                }
            }
        }

        if (!valido) {
            printf("Erro: Voce deve digitar obrigatoriamente 4 numeros.\n\n");
        }
        if (ano > 2026) {
            valido = 0;
            printf("Erro: O ano não pode ser no futuro (maior que 2026).\n\n");
        }
    }
    return ano;
}

void cadastrarLivro() {
    Livro l;

    

    printf("Titulo: ");
    fgets(l.titulo, sizeof(l.titulo), stdin);
    l.titulo[strcspn(l.titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(l.autor, sizeof(l.autor), stdin);
    l.autor[strcspn(l.autor, "\n")] = '\0';

    printf("Editora: ");
    fgets(l.Editora, sizeof(l.Editora), stdin);
    l.Editora[strcspn(l.Editora, "\n")] = '\0';
        
    l.edicao = verificar_ano();
    l.disponivel = 1;
    l.estado = DISPONIVEL;
    l.id = gerar_id_Livro();
    livros[totalLivros++] = l;
    printf("\nID: %d\n", l.id);

    

    printf("Livro cadastrado!\n");
}

// esperarVoltar moved to utils.c

void listarLivros() {
    printf("\n===== LIVROS =====\n");

    for (int i = 0; i < totalLivros; i++) {
        printf("ID: %d\n", livros[i].id);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);
        printf("Editora: %s\n", livros[i].Editora);
        printf("Edição(ano): %d\n", livros[i].edicao);

        if (livros[i].disponivel) {
            printf("Status: Disponivel\n\n");
        } else {
            
           for (int j = 0; j < totalEmprestimos; j++) {
            if (emprestimos[j].idLivro == livros[i].id) {
                int idLeitor = emprestimos[j].idLeitor;
                Leitor *le = buscarLeitorPorId(idLeitor);
                printf("Status: Emprestado para %s\n\n",
                       le != NULL ? le->nome : "Leitor nao encontrado");
            }
           }
        }
    }

    esperarVoltar();
}



