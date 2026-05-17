#include <stdio.h>
#include <stdlib.h>

int lerOpcao(int min, int max) {
    char entrada[50];
    char *end;
    long valor;

    fgets(entrada, sizeof(entrada), stdin);
    valor = strtol(entrada, &end, 10);

    if (end == entrada) return -1;
    if (*end != '\n') return -1;
    if (valor < min || valor > max) return -1;

    return (int) valor;
}

void esperarVoltar(void) {
    int op;
    do {
        printf("\nDigite 0 para voltar: ");
        op = lerOpcao(0, 0);
    } while (op != 0);
}