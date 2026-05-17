#include <stdio.h>
#include <string.h>
#include "emprestimo.h"
#include "leitor.h"
#include "livro.h"
#include "utils.h"
#include "relatorio.h"

#define RESET_CURSOR "\033[H"

#define MAX_EMPRESTIMOS 100
Emprestimo emprestimos[MAX_EMPRESTIMOS];

int totalEmprestimos = 0;

void listarLeitores1() {
    printf("\n===== LEITORES =====\n");
    for (int i = 0; i < totalLeitores; i++) {
        printf("%d - %s (Divida: R$ %.2f)\n",
               leitores[i].id, leitores[i].nome, leitores[i].dividas);
    }

}

void listarEmprestimosPendentes() {
    printf("\n===== EMPRESTIMOS PENDENTES =====\n");

    if (totalEmprestimos == 0) {
        printf("Nao ha emprestimos pendentes no sistema.\n");
        return;
    }

    for (int i = 0; i < totalEmprestimos; i++) {
        int idLivro = emprestimos[i].idLivro;
        int idLeitor = emprestimos[i].idLeitor;
        Livro *livro = buscarLivroPorId(idLivro);
        Leitor *leitor = buscarLeitorPorId(idLeitor);

        printf("\nID do livro: %d\n", idLivro);
        printf("Livro: %s\n", livro != NULL ? livro->titulo : "Livro nao encontrado");
        printf("Leitor: %s\n", leitor != NULL ? leitor->nome : "Leitor nao encontrado");
        printf("Dias em emprestimo: %d\n", emprestimos[i].dias);
        printf("-----------------------------\n");
    }

    esperarVoltar();
}

void emprestarLivro() {
    int idLivro = -1, idLeitor = -1;
    char buf[64];

    while (1) {
        printf("\nID do livro: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return;
        if (sscanf(buf, "%d", &idLivro) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }
        Livro *lv = buscarLivroPorId(idLivro);
        if (lv == NULL) {
            printf("Livro nao encontrado. Tente novamente.\n");
            continue;
        }
        if (!lv->disponivel) {
            printf("Livro indisponivel. Escolha outro.\n");
            continue;
        }
        break;
    }

    listarLeitores1();

    while (1) {
        printf("Escolha o leitor (ID): ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return;
        if (sscanf(buf, "%d", &idLeitor) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }
        Leitor *le = buscarLeitorPorId(idLeitor);
        if (le == NULL) {
            printf("Leitor nao encontrado. Tente novamente.\n");
            continue;
        }
        break;
    }

    // registrar emprestimo
    for (int i = 0; i < totalLivros; i++) {
        if (livros[i].id == idLivro && livros[i].disponivel) {

            livros[i].disponivel = 0;
            livros[i].estado = EMPRESTADO;

            if (totalEmprestimos < MAX_EMPRESTIMOS) {
                emprestimos[totalEmprestimos].idLivro = idLivro;
                emprestimos[totalEmprestimos].idLeitor = idLeitor;
                emprestimos[totalEmprestimos].dias = 0;
                emprestimos[totalEmprestimos].diaEmprestimo = 0;

                totalEmprestimos++;

                printf("Emprestimo realizado!\n");
                return;
            } else {
                printf("Limite de emprestimos atingido!\n");
                return;
            }
        }
    }

    printf("Livro indisponivel!\n");
}

void renovarEmprestimo() {
    int id;

    listarEmprestimosPendentes();

    if (totalEmprestimos == 0) {
        return;
    }

    char buf[64];
    while (1) {
        printf("\nID do livro: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return;
        if (sscanf(buf, "%d", &id) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }
        for (int i = 0; i < totalEmprestimos; i++) {
            if (emprestimos[i].idLivro == id) {
                emprestimos[i].dias += 7;
                printf("Emprestimo renovado!\n");
                return;
            }
        }
        printf("Emprestimo nao encontrado. Tente novamente.\n");
    }
}

void devolucao(){
    int id;
    int tipoDevolucao; 

    listarEmprestimosPendentes();

    if (totalEmprestimos == 0) {
        return;
    }

    
    char buf[64];

    while (1) {
        printf("\nID do livro: ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return;
        if (sscanf(buf, "%d", &id) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }

        printf("1 - Devolucao normal\n");
        printf("2 - Livro danificado (acrescimo de R$ 10,00)\n");
        printf("3 - Livro imprestavel\n");

        while (1) {
            printf("Escolha o tipo de devolucao: ");
            if (fgets(buf, sizeof(buf), stdin) == NULL) return;
            if (sscanf(buf, "%d", &tipoDevolucao) != 1) {
                printf("Entrada invalida. Tente novamente.\n");
                continue;
            }
            if (tipoDevolucao < 1 || tipoDevolucao > 3) {
                printf("Opcao invalida. Escolha 1, 2 ou 3.\n");
                continue;
            }
            break;
        }

        int found = 0;
        for (int i = 0; i < totalEmprestimos; i++) {
            if (emprestimos[i].idLivro == id) {
                found = 1;
                int idLeitor = emprestimos[i].idLeitor;
                int dias = emprestimos[i].dias;

                Leitor *le = buscarLeitorPorId(idLeitor);
                if (dias > 7 && le != NULL) {
                    float multa = (dias - 7) * 2.0f;
                    le->dividas += multa;
                    printf("Multa aplicada: R$ %.2f\n", multa);
                }

                if (tipoDevolucao == 2 && le != NULL) {
                    le->dividas += 10.0f;
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
        if (!found) {
            printf("Emprestimo nao encontrado. Tente novamente.\n");
            continue;
        }
    }
}


void avancarDias() {

    int dias;
    char buf[64];
    while (1) {
        printf("Quantos dias avancar? ");
        if (fgets(buf, sizeof(buf), stdin) == NULL) return;
        if (sscanf(buf, "%d", &dias) != 1) {
            printf("Entrada invalida. Tente novamente.\n");
            continue;
        }
        if (dias < 0) {
            printf("Numero de dias invalido.\n");
            continue;
        }
        break;
    }

    for (int i = 0; i < totalEmprestimos; i++) {
        emprestimos[i].dias += dias;
    }

    printf("Tempo avancado!\n");
}
