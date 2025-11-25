#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define QUANT_MAX_PECAS 5 //constante com a quantidade de pecas

static int contador = 0;

int numItensAtual = 0;
const char PECAS_PADRAO[] = "IOTL";

typedef struct {
    int id;
    char nome;
} Peca;
Peca* pecas;

bool isQuantidadeMaximaAtingida(){
    return numItensAtual >= QUANT_MAX_PECAS;
}

Peca gerarPeca(){

    Peca novaPeca;

    if (isQuantidadeMaximaAtingida()){
        printf("[falha] Quantidade máxima de pecas atingidas!");
        return novaPeca;
    }

    // função que número aleatorio
    int idxAleatorio = rand() % strlen(PECAS_PADRAO);

    novaPeca.id = contador++;
    novaPeca.nome = PECAS_PADRAO[idxAleatorio];

    return novaPeca;
}

void dequeue(Peca* pecas){

    printf("=== Jogar peça (dequeue) ===\n\n");

    if(numItensAtual == 0){
        printf("Fila vazia\n");
        return;
    }

    Peca pecaRetirada = pecas[0];

    // andar com a fila
    for (int i = 0; i < numItensAtual - 1; i++) {
        pecas[i] = pecas[i + 1];
    }

    printf("Retirado peça %c\n", pecaRetirada.nome);
    numItensAtual--;

}

void enqueue(Peca* pecas){

    printf("=== Inserir nova peça (enqueue) ===\n\n");

    if(isQuantidadeMaximaAtingida()){
        printf("Fila cheia\n");
        return;
    }

    Peca novaPeca = gerarPeca();
    pecas[numItensAtual] = novaPeca;

    printf("Adicionado peça %c\n", novaPeca.nome);

    numItensAtual++;

}

void verFila(Peca* pecas){

    printf("=== Ver lista de peças ===\n\n");

    if(numItensAtual == 0){
        printf("Fila vazia\n");
        return;
    }

    for (int i = 0; i < numItensAtual; i++) {
        printf("[%c %d] ", pecas[i].nome, pecas[i].id);
    }
    printf("\n");

}

// -- FUNCOES ESPECIFICAS

// funcao para liberar memoria e encerrar o programa
void finalizarJogo(){
    printf("Finalizando o jogo...\n");
    free(pecas);
    exit(0);
}

// função com código para limpar o terminal/cmd
void limpaTela(){
    printf("\033[2J\033[H");
}

int exibirOpcoesMenu(){
    int opcao = -1;
    
    printf("\n=== Menu ===\n\n");
    printf("Quantidade de pecas: %d/%d \n", numItensAtual, QUANT_MAX_PECAS);
    printf("1. Jogar peça (dequeue)\n");
    printf("2. Inserir nova peça (enqueue)\n");
    printf("3. Ver lista de peças\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    
    return opcao;
}

void exibirMenu(){
    
    int opcao;
    
    do {
        
        opcao = NULL;
        opcao = exibirOpcoesMenu();
        
        limpaTela();
        
        switch(opcao) {
            case 1: dequeue(pecas); break;
            case 2: enqueue(pecas); break;
            case 3: verFila(pecas); break;
            case 0: finalizarJogo(); break;
            default: printf("Opcao invalida!\n");
        }
        
    } while(opcao != 0);
    
}

// -- FUNCAO PRINCIPAL

int main() {
    
    printf("=== Desafio Tetris Stack – Tema 3 ===\n");
    
    pecas = (Peca*) calloc(QUANT_MAX_PECAS, sizeof(Peca));

    exibirMenu();

    free(pecas);
    return 0;
}
