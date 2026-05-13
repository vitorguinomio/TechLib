#ifndef EMPRESTIMOS_H
#define EMPRESTIMOS_H
#include "livro.h"
#define MAX_EMPRESTIMOS 100

typedef struct Emprestimo {
    int idLivro;
    int idLeitor;
    char usuario[50];
    int dias;
    int diaEmprestimo;
} Emprestimo;

extern int totalEmprestimos;
extern Emprestimo emprestimos[MAX_EMPRESTIMOS];


void listarEmprestimosPendentes();
void emprestarLivro();
void renovarEmprestimo();
void devolucao();
void avancarDias();

#endif




