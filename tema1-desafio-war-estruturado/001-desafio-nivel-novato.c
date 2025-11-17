#include <stdio.h>

#define QUANT_TERRITORIOS 5 //constante com a quantidade de territorios

// criação de struct Territorio com 3 itens - Structs agrupa variáveis diferentes para oganizar o código;

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

int main() {

    Territorio territorios[QUANT_TERRITORIOS];
    int i;

    printf("=== Desafio War Estruturado - Tema 1 ===\n");

    // - Entrada de dados: usando for para alimentar o array de 5 territórios

    printf("=== Cadastro de territórios ===\n");

    for (i = 0; i < QUANT_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);

        // %29[^\n] - Le o input todo

        printf("Nome: ");
        scanf(" %29[^\n]", territorios[i].nome);

        printf("Cor do exercito: ");
        scanf(" %9[^\n]", territorios[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // - Saída de dados: usando for para exibir dados do array de 5 territórios

    printf("\n=== Exibe territórios Cadastrados ===\n");

    for (i = 0; i < QUANT_TERRITORIOS; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
    }

    return 0;
}
