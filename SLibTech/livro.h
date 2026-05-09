#ifndef LIVROS_H
#define LIVROS_H
#define MAX_LIVROS 100

typedef enum {
    DISPONIVEL,
    EMPRESTADO,
    DANIFICADO,
    IMPRESTAVEL
} EstadoLivro;

typedef struct {

    int id;
    char titulo[50];
    char autor[50];
    int disponivel;

    EstadoLivro estado;

} Livro;

extern Livro livros[MAX_LIVROS];
extern int totalLivros;

void listarLivros();
void cadastrarLivro();
void emprestarLivro();
void renovarEmprestimo();
void devolucao();
void avancarDias();

#endif




