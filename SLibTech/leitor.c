#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "leitor.h"
#include "utils.h"

Leitor leitores[MAX_LEITORES] = {
    {1 ,"Joao", "111", "9999", 0},
    {2 ,"Maria", "222", "8888", 0},
    {3 ,"Pedro", "333", "7777", 0},
    {4 ,"Ana", "444", "6666", 0},
    {5 ,"Lucas", "555", "5555", 0}
};

int totalLeitores = 5;

int gerar_id() {
    int max_id = 0;
    for (int i = 0; i <totalLeitores ; i++) {
        if (leitores[i].id > max_id) {
            max_id = leitores[i].id;
        }
    }
    return max_id + 1;
}

int validar_cpf(const char *cpf_entrada) {
    int digitos[11];
    int count = 0;

    // 1. Extrai apenas os números da string (ignora pontos e traços)
    for (int i = 0; cpf_entrada[i] != '\0'; i++) {
        if (isdigit(cpf_entrada[i])) {
            if (count < 11) {
                // Converte o caractere ASCII para o número inteiro real
                digitos[count] = cpf_entrada[i] - '0'; 
            }
            count++;
        }
    }

    // Se o usuário digitou mais ou menos de 11 números, é inválido
    if (count != 11) {
        return 0;
    }

    // 2. Filtro de CPFs com todos os números iguais (falsos-positivos)
    int todos_iguais = 1;
    for (int i = 1; i < 11; i++) {
        if (digitos[i] != digitos[0]) {
            todos_iguais = 0;
            break;
        }
    }
    if (todos_iguais) {
        return 0; 
    }

    // 3. Cálculo do PRIMEIRO dígito verificador
    int soma1 = 0;
    for (int i = 0; i < 9; i++) {
        soma1 += digitos[i] * (10 - i);
    }
    int resto1 = (soma1 * 10) % 11;
    if (resto1 == 10) {
        resto1 = 0;
    }
    
    // Verifica se o primeiro dígito calculado bate com o digitado
    if (resto1 != digitos[9]) {
        return 0;
    }

    // 4. Cálculo do SEGUNDO dígito verificador
    int soma2 = 0;
    for (int i = 0; i < 10; i++) {
        soma2 += digitos[i] * (11 - i);
    }
    int resto2 = (soma2 * 10) % 11;
    if (resto2 == 10) {
        resto2 = 0;
    }

    // Verifica se o segundo dígito calculado bate com o digitado
    if (resto2 != digitos[10]) {
        return 0;
    }
 
    return 1;
}


void cadastrarLeitor() {
    Leitor l;
    char cpf_cadastrado[20];
    int cpf_valido = 0;

    printf("\n--- Novo Cadastro de Leitor ---\n");

    printf("Nome: ");
    fgets(l.nome, sizeof(l.nome), stdin);
    l.nome[strcspn(l.nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(l.telefone, sizeof(l.telefone), stdin);
    l.telefone[strcspn(l.telefone, "\n")] = '\0';

    while (!cpf_valido) {
        printf("CPF: ");
        if (fgets(cpf_cadastrado, sizeof(cpf_cadastrado), stdin) != NULL) {

            cpf_cadastrado[strcspn(cpf_cadastrado, "\n")] = '\0'; 

            if (validar_cpf(cpf_cadastrado)) {
                strcpy(l.cpf, cpf_cadastrado); 
                cpf_valido = 1;
            } else {
                printf("Erro: CPF invalido. Tente novamente.\n\n");
            }
        }
    }
    
    l.id = gerar_id(); 
    printf("\nID do Leitor gerado: %d\n", l.id);

    leitores[totalLeitores++] = l;
    printf("Leitor cadastrado com sucesso!\n"); 
}

void listarLeitores() {
    printf("\n===== LEITORES =====\n");
    for (int i = 0; i < totalLeitores; i++) {
        printf("%d - %s (Divida: R$ %.2f)\n",
               leitores[i].id, leitores[i].nome, leitores[i].dividas);
    }

    esperarVoltar();
}

Leitor *buscarLeitorPorId(int id) {
    for (int i = 0; i < totalLeitores; i++) {
        if (leitores[i].id == id) return &leitores[i];
    }
    return NULL;
}