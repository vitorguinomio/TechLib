#include <stdio.h>
#include "menu.h"
#include "livro.h"
#include "relatorio.h"
#include "utils.h"

void menu() {
    int op;

    do {
        printf("\n===== SISTEMA BIBLIOTECA =====\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Listar Livros\n");
        printf("3 - Emprestar Livro\n");
        printf("4 - Renovar Emprestimo\n");
        printf("5 - Devolução de Livros\n");
        printf("6 - Avançar Dias\n");
        printf("7 - Relatórios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        op = lerOpcao(0, 7);

        if (op == -1) {
            printf("Opcao invalida!\n");
            continue;
        }

        switch(op) {
            case 1: cadastrarLivro(); break;
            case 2: listarLivros(); break;
            case 3: emprestarLivro(); break;
            case 4: renovarEmprestimo(); break;
            case 5: devolucao();break;
            case 6: avancarDias();break;
            case 7: menuRelatorios(); break;
        }

    } while(op != 0);
}