#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define QUANT_TERRITORIOS 5 //constante com a quantidade de territorios

// criação de struct Territorio com 3 itens - Structs agrupa variáveis diferentes para oganizar o código;

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

Territorio* territorios;

int cadastrarTerritorios(){
    
    printf("=== Cadastro de territórios ===\n");
    
    for (int i = 0; i < QUANT_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        
        // %29[^\n] - Le o input todo
        
        printf("Nome: ");
        scanf(" %29[^\n]", territorios[i].nome);
        
        printf("Cor do exercito: ");
        scanf(" %9[^\n]", territorios[i].cor);
        
        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    return 0;
}

int exibirTerritorios(){
    
    printf("\n=== Exibe territórios ===\n");
    
    for (int i = 0; i < QUANT_TERRITORIOS; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor: %s\n", territorios[i].cor);
        printf("Tropas: %d\n", territorios[i].tropas);
        printf("\n");
    }

    return 0;
}

int rolarDado() {

    // porque modulo % 6? pq resto nunca pode ser igual ou maior que o divisor.
    return (rand() % 6) + 1;
}

int atacar(Territorio* atacante, Territorio* defensor) {

    printf("\n=== Fase de ataque ===\n");

    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();
    
    printf("%s (jogador atacante) rolou um dado e tirou %d\n", atacante->nome, dadoAtacante);
    printf("%s (jogador defensor) rolou um dado e tirou %d\n", defensor->nome, dadoDefensor);
    
    // verifica ganhador e perdedor

    Territorio* ganhador;
    Territorio* perdedor;

    if (dadoAtacante == dadoDefensor) {
        printf("Empate ninguem ganhou \n");
    }else{

        if (dadoAtacante > dadoDefensor) {
            ganhador = atacante;
            perdedor = defensor;
        } else {
            ganhador = defensor;
            perdedor = atacante;
        }

        printf("%s vence! %s perdeu 1 tropa \n", ganhador->nome, perdedor->nome);
        perdedor->tropas--;
        ganhador->tropas++;

        // verifica consquista de territorio
    
        if(perdedor->tropas <= 0){
            printf("Conquista! Território %s foi dominado pelo Exercito %s\n", perdedor->nome, ganhador->nome);
            strcpy(perdedor->cor,ganhador->cor);
        }
    }

    return 0;
}

int finalizarJogo(){
    free(territorios);
    exit(0);
}

int exibirMenu(){

    int opcao;
    
    do {
        printf("\n=== Menu do War ===\n");
        printf("1. Atacar\n");
        printf("2. Exibir status\n");
        printf("3. Finalizar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            
            case 1:
            exibirTerritorios();
            int atacanteIndex, defensorIndex;
            printf("Escolha o territorio atacante (numero): ");
            scanf("%d", &atacanteIndex);
            printf("Escolha o territorio defensor (numero): ");
            scanf("%d", &defensorIndex);
            
            if (atacanteIndex < 1 ||
                atacanteIndex >  QUANT_TERRITORIOS ||
                defensorIndex < 1 ||
                defensorIndex > QUANT_TERRITORIOS ||
                atacanteIndex == defensorIndex
            ) {
                printf("Indice invalido!\n");
                break;
            }
            
            atacar(&territorios[atacanteIndex-1], &territorios[defensorIndex-1]);
            break;
            
            case 2:
            exibirTerritorios();
            break;
            
            case 3:
            printf("Finalizando o jogo...\n");
            finalizarJogo();
            break;
            
            default:
            printf("Opcao invalida!\n");
        }
        
    } while(opcao != 4);

    return 0;

}

int main() {

    // inicializa aleatoriedade
    srand(time(NULL)); 
    
    printf("=== Desafio War Estruturado - Tema 1 ===\n");
    
    territorios = (Territorio*) malloc(QUANT_TERRITORIOS * sizeof(Territorio));

    cadastrarTerritorios();
    exibirTerritorios();

    exibirMenu();
    
    free(territorios);
    return 0;
}


