#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define QUANT_TERRITORIOS 5 //constante com a quantidade de territorios
#define QUANT_MISSOES 5 //constante com a quantidade de missoes

// criação de struct Territorio com 3 itens - Structs agrupa variáveis diferentes para oganizar o código;

typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

Territorio* territorios;

// array de missoes

const char* missoes[QUANT_MISSOES] = {
    "Conquistar 3 territorios cor azul",
    "Eliminar todas as tropas da cor vermelha",
    "Eliminar todas as tropas da cor verde",
    "Possuir mais de 5 tropas da cor preta",
    "Eliminar todas as tropas da cor amarela"
};

int indexNumeroMissaoSelecionada;

// -- FUNCOES ESPECIFICAS

int cadastrarTerritorios(){
    
    printf("=== Cadastro de territórios ===\n");
    
    for (int i = 0; i < QUANT_TERRITORIOS; i++) {
        printf("\n--- Território %d ---\n", i + 1);
        
        // %29[^\n] - Le o input todo
        
        printf("Nome: ");
        scanf(" %29[^\n]", territorios[i].nome);
        
        printf("Cor do exercito (Digite uma das cores: azul, vermelha, verde, preta, amarela): ");
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
    }
    printf("\n");

    return 0;
}

// função que número aleatorio de 1 a 6
int rolarDado() {
    // porque modulo % 6? pq resto nunca pode ser igual ou maior que o divisor.
    return (rand() % 6) + 1;
}

// função com código para limpar o terminal/cmd
void limpaTela(){
    printf("\033[2J\033[H");
}

int atacar(Territorio* atacante, Territorio* defensor) {

    printf("\n=== Fase de ataque ===\n");

    int dadoAtacante = rolarDado();
    int dadoDefensor = rolarDado();
    
    printf("%s (jogador atacante) rolou um dado e tirou %d\n", atacante->nome, dadoAtacante);
    printf("%s (jogador defensor) rolou um dado e tirou %d\n", defensor->nome, dadoDefensor);
    
    // verifica ganhador e perdedor
    // foi criado territorio "ganhador" e "perdedor" para processar o resultado da batalha

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

        // verifica conquista de territorio
    
        if(perdedor->tropas <= 0){
            printf("Conquista! Território %s foi dominado pelo Território %s\n", perdedor->nome, ganhador->nome);
            strcpy(perdedor->cor, ganhador->cor);
        }
    }

    return 0;
}

void exibirMissoes(){

    printf("\n=== Exibe missões ===\n");
    
    for (int i = 0; i < QUANT_MISSOES; i++) {
        printf(" - %s\n", missoes[i]);
    }
    printf("\n");

}

// funcao para selecionar uma missão de forma aleatoria
void atribuirMissao(){
    indexNumeroMissaoSelecionada = rand() % QUANT_MISSOES;
}

void exibirMissaoSelecionada(){
    printf(" Sua missão(%d): %s\n", indexNumeroMissaoSelecionada, missoes[indexNumeroMissaoSelecionada]);
}

int verificarMissao(){

    int quantTropas;
    
    switch(indexNumeroMissaoSelecionada) {

        case 0:{  // "Conquistar 3 territorios cor azul",
            int quantTerritoriosConquistados = 0;
            for (int i = 0; i < sizeof(territorios); i++) {
                if( strcmp( territorios[i].cor, "azul") ) quantTerritoriosConquistados++;
            }
            return quantTerritoriosConquistados >= 3;
        }

        case 1: { // "Eliminar todas as tropas da cor vermelha",
            quantTropas = 0;
            for (int i = 0; i < sizeof(territorios); i++) {
                if( strcmp( territorios[i].cor, "vermelha") ) quantTropas++;
            }
            return quantTropas <= 0;
        }

        case 2: { // "Eliminar todas as tropas da cor verde",
            quantTropas = 0;
            for (int i = 0; i < sizeof(territorios); i++) {
                if( strcmp( territorios[i].cor, "verde") ) quantTropas++;
            }
            return quantTropas <= 0;
        }

        case 3: { // "Possuir mais de 5 tropas da cor preta",
            quantTropas = 0;
            for (int i = 0; i < sizeof(territorios); i++) {
                if( strcmp( territorios[i].cor, "preta") ) quantTropas+=territorios[i].tropas;
            }
            return quantTropas >= 5;
        }

        case 4: { // "Eliminar todas as tropas da cor amarela"
            quantTropas = 0;
            for (int i = 0; i < sizeof(territorios); i++) {
                if( strcmp( territorios[i].cor, "amarela") ) quantTropas++;
            }
            return quantTropas <= 0;
        }

        default:
            return 0; // missão inválida
    }
}

// funcao para liberar memoria e encerrar o programa
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
        printf("3. Exibir missao\n");
        printf("4. Finalizar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            
            case 1:
            limpaTela();
            exibirTerritorios();

            int atacanteIndex, defensorIndex;
            printf("Escolha o territorio atacante (numero): ");
            scanf("%d", &atacanteIndex);
            printf("Escolha o territorio defensor (numero): ");
            scanf("%d", &defensorIndex);
            
            // verifica se atacante e defensor existem pelos indices informados

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
            
            // verifica que missão foi concluida após um ataque

            if( verificarMissao() ){
                printf("[missão] Parabéns! Missão completada: %s\n", missoes[indexNumeroMissaoSelecionada]);
            } else {
                printf("[missão] Complete sua missão: %s\n", missoes[indexNumeroMissaoSelecionada]);
            
            }

            break;
            
            case 2:
            limpaTela();
            exibirTerritorios();
            break;
            
            case 3:
            limpaTela();
            exibirMissaoSelecionada();
            break;
            
            case 4:
            limpaTela();
            printf("Finalizando o jogo...\n");
            finalizarJogo();
            break;
            
            default:
            printf("Opcao invalida!\n");
        }
        
    } while(opcao != 4);

    return 0;

}

// -- FUNCAO PRINCIPAL

int main() {

    // inicializa aleatoriedade
    srand(time(NULL)); 

    territorios = (Territorio*) malloc(QUANT_TERRITORIOS * sizeof(Territorio));
    
    printf("=== Desafio War Estruturado - Tema 1 ===\n");
    
    cadastrarTerritorios();
    
    exibirMissoes();
    atribuirMissao();
    exibirMissaoSelecionada();

    exibirMenu();
    
    free(territorios);
    return 0;
}


