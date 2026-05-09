#include <stdio.h>
#include "relatorio.h"
#include "livro.h"
#include "leitor.h"
#include "emprestimo.h"
#include "estado.h"

void relatorioEmprestimos(int periodo) {

    printf("\n===== RELATORIO DE EMPRESTIMOS =====\n");

    int encontrou = 0;

    for (int i = 0; i < totalEmprestimos; i++) {

        int diferenca = emprestimos[i].dias;

        if (diferenca <= periodo) {

            encontrou = 1;

            int idLivro = emprestimos[i].idLivro;
            int idLeitor = emprestimos[i].idLeitor;

            printf("\nLivro: %s\n",
                   livros[idLivro].titulo);

            printf("Leitor: %s\n",
                   leitores[idLeitor].nome);

            printf("Dias desde emprestimo: %d\n",
                   diferenca);

            printf("-----------------------------\n");
        }
    }

    if (!encontrou) {
        printf("Nenhum emprestimo encontrado.\n");
    }

    int op;

    printf("\nDigite 0 para voltar: ");

    while (scanf("%d", &op) != 1 || op != 0) {

        printf("Digite 0 para voltar: ");

        while(getchar() != '\n');
    }

    getchar();
}


void relatorioLivrosDanificados() {

    printf("\n===== LIVROS DANIFICADOS =====\n");

    int encontrou = 0;

    for (int i = 0; i < totalLivros; i++) {

        if (livros[i].estado == DANIFICADO ||
            livros[i].estado == IMPRESTAVEL) {

            encontrou = 1;

            printf("\nID: %d\n", livros[i].id);

            printf("Titulo: %s\n",
                   livros[i].titulo);

            printf("Autor: %s\n",
                   livros[i].autor);

            printf("Estado: %s\n",
                   textoEstado(livros[i].estado));

            printf("-----------------------------\n");
        }
    }

    if (!encontrou) {
        printf("Nenhum livro danificado.\n");
    }

    int op;

    printf("\nDigite 0 para voltar: ");

    while (scanf("%d", &op) != 1 || op != 0) {

        printf("Digite 0 para voltar: ");

        while(getchar() != '\n');
    }

    getchar();
}


void relatorioLeitoresComDivida() {

    printf("\n===== LEITORES COM DIVIDAS =====\n");

    int encontrou = 0;

    for (int i = 0; i < MAX_LEITORES; i++) {

        if (leitores[i].dividas > 0) {

            encontrou = 1;

            printf("\nNome: %s\n",
                   leitores[i].nome);

            printf("CPF: %s\n",
                   leitores[i].cpf);

            printf("Telefone: %s\n",
                   leitores[i].telefone);

            printf("Divida: R$ %.2f\n",
                   leitores[i].dividas);

            printf("-----------------------------\n");
        }
    }

    if (!encontrou) {
        printf("Nenhum leitor com dividas.\n");
    }

    int op;

    printf("\nDigite 0 para voltar: ");

    while (scanf("%d", &op) != 1 || op != 0) {

        printf("Digite 0 para voltar: ");

        while(getchar() != '\n');
    }

    getchar();
}


void pagamentoDividaLeitor() {

    int leitorEscolhido;
    float valorPago;

    printf("\n===== PAGAMENTO DE DIVIDA =====\n");

    for (int i = 0; i < MAX_LEITORES; i++) {

        if (leitores[i].dividas > 0) {
            printf("%d - %s (Divida: R$ %.2f)\n",
                   i,
                   leitores[i].nome,
                   leitores[i].dividas);
        }
    }

    printf("\nEscolha o leitor: ");
    if (scanf("%d", &leitorEscolhido) != 1) {
        printf("Entrada invalida!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    if (leitorEscolhido < 0 || leitorEscolhido >= MAX_LEITORES || leitores[leitorEscolhido].dividas <= 0) {
        printf("Leitor invalido ou sem divida.\n");
        return;
    }

    printf("Valor a pagar: R$ ");
    if (scanf("%f", &valorPago) != 1) {
        printf("Entrada invalida!\n");
        while (getchar() != '\n');
        return;
    }
    getchar();

    if (valorPago <= 0) {
        printf("Valor invalido!\n");
        return;
    }

    leitores[leitorEscolhido].dividas -= valorPago;
    if (leitores[leitorEscolhido].dividas < 0) {
        leitores[leitorEscolhido].dividas = 0;
    }

    printf("Pagamento realizado. Divida atual: R$ %.2f\n",
           leitores[leitorEscolhido].dividas);

    printf("\nDigite 0 para voltar: ");
    while (scanf("%d", &leitorEscolhido) != 1 || leitorEscolhido != 0) {
        printf("Digite 0 para voltar: ");
        while (getchar() != '\n');
    }
    getchar();
}


void menuRelatorios() {

    int op;

    do {

        printf("\n===== RELATORIOS =====\n");

        printf("1 - Emprestimos ultimos 7 dias\n");
        printf("2 - Emprestimos ultimos 15 dias\n");
        printf("3 - Emprestimos ultimos 30 dias\n");
        printf("4 - Livros danificados\n");
        printf("5 - Leitores com dividas\n");
        printf("6 - Pagamento de divida\n");
        printf("0 - Voltar\n");

        printf("Escolha: ");

        if (scanf("%d", &op) != 1) {

            printf("Entrada invalida!\n");

            while(getchar() != '\n');

            continue;
        }

        getchar();

        switch(op) {

            case 1:
                relatorioEmprestimos(7);
                break;

            case 2:
                relatorioEmprestimos(15);
                break;

            case 3:
                relatorioEmprestimos(30);
                break;

            case 4:
                relatorioLivrosDanificados();
                break;

            case 5:
                relatorioLeitoresComDivida();
                break;

            case 6:
                pagamentoDividaLeitor();
                break;

            case 0:
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(op != 0);
}