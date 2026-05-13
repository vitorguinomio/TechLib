#include <stdio.h>
#include "menu.h"
#include "livro.h"
#include "relatorio.h"
#include "utils.h"
#include "leitor.h"

void menu() {
    int op;

    do {
        printf("\n===== SISTEMA BIBLIOTECA =====\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Cadastra Leitores\n");
        printf("3 - Listar Leitores\n");
        printf("4 - Listar Livros\n");
        printf("5 - Emprestar Livro\n");
        printf("6 - Renovar Emprestimo\n");
        printf("7 - Devolução de Livros\n");
        printf("8 - Avançar Dias\n");
        printf("9 - Relatórios\n");
        printf("0 - Sair\n");
        printf("Escolha: ");

        op = lerOpcao(0, 9);

        if (op == -1) {
            printf("Opcao invalida!\n");
            continue;
        }

        switch(op) {
            case 1: cadastrarLivro(); break;
            case 2: cadastrarLeitor();break;
            case 3: listarLeitores(); break;
            case 4: listarLivros(); break;
            case 5: emprestarLivro(); break;
            case 6: renovarEmprestimo();break;
            case 7: devolucao();break;
            case 8: avancarDias(); break;
            case 9: menuRelatorios();break;
        }

    } while(op != 0);
}