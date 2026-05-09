#include <stdio.h>
#include <string.h>
#include "livro.h"
#include "emprestimo.h"
#include "leitor.h"

#define RESET_CURSOR "\033[H"

Livro livros[MAX_LIVROS] = {
    {1, "Alice no pais das maravilhas", "Lewis Carroll", 1, DISPONIVEL},
    {2, "Sense Life", "Glitch Tellend", 1, DISPONIVEL},
    {3, "Depressao para leigos", "John Preston", 1, DISPONIVEL},
    {4, "A sutil arte de ligar o foda-se", "Mark Manson", 1, DISPONIVEL},
    {5, "Chapeuzinho vermelho", "Charles Perrault", 1, DISPONIVEL}
};

int totalLivros = 5;

void cadastrarLivro() {
    Livro l;

    printf("\nID: ");
    scanf("%d", &l.id);
    getchar(); // limpa buffer

    printf("Titulo: ");
    fgets(l.titulo, sizeof(l.titulo), stdin);
    l.titulo[strcspn(l.titulo, "\n")] = '\0';

    printf("Autor: ");
    fgets(l.autor, sizeof(l.autor), stdin);
    l.autor[strcspn(l.autor, "\n")] = '\0';

    l.disponivel = 1;
    l.estado = DISPONIVEL;
    livros[totalLivros++] = l;

    printf("Livro cadastrado!\n");
}

void esperarVoltar() {
    int op;

    printf("\nDigite 0 para voltar: ");

    while (scanf("%d", &op) != 1 || op != 0) {
        printf("Entrada invalida! Digite 0: ");
        while(getchar() != '\n');
    }

    getchar(); 
}

void listarLivros() {
    printf("\n===== LIVROS =====\n");

    for (int i = 0; i < totalLivros; i++) {
        printf("ID: %d\n", livros[i].id);
        printf("Titulo: %s\n", livros[i].titulo);
        printf("Autor: %s\n", livros[i].autor);

        if (livros[i].disponivel) {
            printf("Status: Disponivel\n\n");
        } else {
            
           for (int j = 0; j < totalEmprestimos; j++) {
            if (emprestimos[j].idLivro == livros[i].id) {

            int idLeitor = emprestimos[j].idLeitor;
            printf("Status: Emprestado para %s\n\n",
            leitores[idLeitor].nome);
    }
}
        }
    }

    esperarVoltar();
}



