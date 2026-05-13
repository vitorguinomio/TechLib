#ifndef LEITOR_H
#define LEITOR_H

#define MAX_LEITORES 5

typedef struct {
    int id; 
    char nome[50];
    char cpf[20];
    char telefone[20];
    float dividas;
} Leitor;

extern Leitor leitores[MAX_LEITORES];
extern int totalLeitores;

void listarLeitores();
void cadastrarLeitor();
int gerar_id();
#endif