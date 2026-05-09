#include <stdio.h>
#include <string.h>
#include "emprestimo.h"
#include "leitor.h"

#define RESET_CURSOR "\033[H"

#define MAX_EMPRESTIMOS 100
Emprestimo emprestimos[MAX_EMPRESTIMOS];

int totalEmprestimos = 0;

void emprestarLivro() {
    int idLivro, idLeitor;

    printf("\nID do livro: ");
    scanf("%d", &idLivro);
    getchar();

    listarLeitores();

    printf("Escolha o leitor: ");
    scanf("%d", &idLeitor);
    getchar();

    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id == idLivro && livros[i].disponivel) {

            livros[i].disponivel = 0;
            livros[i].estado = EMPRESTADO;

            emprestimos[totalEmprestimos].idLivro = idLivro;
            emprestimos[totalEmprestimos].idLeitor = idLeitor;
            emprestimos[totalEmprestimos].dias = 0;
            emprestimos[totalEmprestimos].diaEmprestimo = 0;

            totalEmprestimos++;

            printf("Emprestimo realizado!\n");
            return;
        }
    }

    printf("Livro indisponivel!\n");
}

void renovarEmprestimo() {
    int id;

    printf("\nID do livro: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == id) {
            emprestimos[i].dias += 7;
            printf("Emprestimo renovado!\n");
            return;
        }
    }

    printf("Nao encontrado!\n");
}

void devolucao(){
    int id;
    int tipoDevolucao;

    printf("\nID do livro: ");
    scanf("%d", &id);
    getchar();

    printf("1 - Devolucao normal\n");
    printf("2 - Livro danificado (acrescimo de R$ 10,00)\n");
    printf("3 - Livro imprestavel\n");
    printf("Escolha o tipo de devolucao: ");
    scanf("%d", &tipoDevolucao);
    getchar();

    for (int i = 0; i < totalEmprestimos; i++) {
        if (emprestimos[i].idLivro == id) {

            int leitor = emprestimos[i].idLeitor;
            int dias = emprestimos[i].dias;

            if (dias > 7) {
                float multa = (dias - 7) * 2.0;
                leitores[leitor].dividas += multa;

                printf("Multa aplicada: R$ %.2f\n", multa);
            }

            if (tipoDevolucao == 2) {
                leitores[leitor].dividas += 10.0f;
                printf("Acrescimo por dano aplicado: R$ 10,00\n");
            }

            for (int j = 0; j < totalLivros; j++) {
                if (livros[j].id == id) {
                    livros[j].disponivel = 1;
                    if (tipoDevolucao == 2) {
                        livros[j].estado = DANIFICADO;
                    } else if (tipoDevolucao == 3) {
                        livros[j].estado = IMPRESTAVEL;
                    } else {
                        livros[j].estado = DISPONIVEL;
                    }
                }
            }

            for (int k = i; k < totalEmprestimos - 1; k++) {
                emprestimos[k] = emprestimos[k + 1];
            }

            totalEmprestimos--;

            printf("Livro devolvido!\n");
            return;
        }
    }

    printf("Emprestimo nao encontrado!\n");
}


void avancarDias() {

    int dias;

    printf("Quantos dias avancar? ");
    scanf("%d", &dias);
    getchar();

    for (int i = 0; i < totalEmprestimos; i++) {
        emprestimos[i].dias += dias;
    }

    printf("Tempo avancado!\n");
}
