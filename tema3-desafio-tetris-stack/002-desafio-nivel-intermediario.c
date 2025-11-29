#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define QUANT_MAX_PECAS_FILA 5 //constante com a quantidade de pecas na fila
#define QUANT_MAX_PECAS_PILHA 3 //constante com a quantidade de pecas reservas

static int contador = 0;

const char PECAS_PADRAO[] = "IOTL";

// Peça

typedef struct {
    int id;
    char nome;
} Peca;

// Fila

typedef struct {
    Peca* itens;
    int capacidadeTotal;
    int tamanhoAtual;
} Fila;
Fila fila;

Fila criarFila(int capacidadeTotal) {
    Fila f;
    f.itens = (Peca*) calloc(capacidadeTotal, sizeof(Peca));
    f.capacidadeTotal = capacidadeTotal;
    f.tamanhoAtual = 0;
    return f;
}

void enqueue(Fila* f, Peca item) {
    if (f->tamanhoAtual == f->capacidadeTotal) {
        printf("Fila cheia!\n");
        return;
    }
    f->itens[f->tamanhoAtual] = item;
    f->tamanhoAtual++;

    printf("Inserido (%c) na fila\n", item.nome);
}

Peca dequeue(Fila* f) {
    if (f->tamanhoAtual == 0) {
        printf("Fila vazia!\n");
        Peca vazio = { -1, '?' };
        return vazio;
    }
    Peca itemRemovido = f->itens[0];
    printf("Removido (%c) da fila\n", itemRemovido.nome);

    // Andar com a fila: Move cada elemento uma posição para a esquerda
    for (int i = 0; i < f->tamanhoAtual - 1; i++) {
        f->itens[i] = f->itens[i + 1];
    }
    
    // Libera um espaço no final da fila
    f->tamanhoAtual--;

    return itemRemovido;
}

// Pilha

typedef struct {
    Peca* itens;
    int capacidadeTotal;
    int tamanhoAtual;
} Pilha;
Pilha pilha;

Pilha criarPilha(int capacidadeTotal) {
    Pilha p;
    p.itens = (Peca*) calloc(capacidadeTotal, sizeof(Peca));
    p.capacidadeTotal = capacidadeTotal;
    p.tamanhoAtual = 0;
    return p;
}

int push(Pilha* p, Peca item) {
    if (p->tamanhoAtual == p->capacidadeTotal) {
        printf("Pilha cheia!\n");
        return 0;
    }
    p->itens[p->tamanhoAtual] = item;
    p->tamanhoAtual++;

    printf("Inserido (%c) na pilha\n", item.nome);

    return 1;
}

Peca pop(Pilha* p) {
    if (p->tamanhoAtual == 0) {
        printf("Pilha vazia!\n");
        Peca vazio = { -1, '?' };
        return vazio;
    }

    Peca itemRemovido = p->itens[ p->tamanhoAtual - 1 ];
    printf("Removido (%c) da pilha\n", itemRemovido.nome);
    
    // Libera um espaço no final/top da pilha
    p->tamanhoAtual--;

    return itemRemovido;
}

Peca gerarPeca(){

    Peca novaPeca;

    // função que número aleatorio
    int idxAleatorio = rand() % strlen(PECAS_PADRAO);

    novaPeca.id = contador++;
    novaPeca.nome = PECAS_PADRAO[idxAleatorio];

    return novaPeca;
}

void verPecas(Fila* f, Pilha* p){

    printf("=== Ver lista de peças ===\n");

    if(f->tamanhoAtual == 0) printf("Vazio...\n");

    for (int i = 0; i < f->tamanhoAtual; i++) {
        printf("[%c %d] ", f->itens[i].nome, f->itens[i].id);
    }
    printf("\n");

    printf("=== Ver pilha de peças ===\n");

    if(p->tamanhoAtual == 0) printf("Vazio...\n");

    for (int i = 0; i < p->tamanhoAtual; i++) {
        printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n");

}

void jogarPeca(Fila* f){
    dequeue(f);
    enqueue(f, gerarPeca());
}

void reservarPeca(Fila* f, Pilha* p){
    
    Peca item = f->itens[0];

    // Tenta colocar peca na pilha antes de remover da fila
    int itemAdicionado = push(p, item);
    
    if(itemAdicionado){
        Peca item = dequeue(f);
        if(item.nome == '?') return; //fila estava vazia 
    }
    
}

void usarPecaReservada(Pilha* p){
    pop(p);
}

void alimentaFila(Fila* f){
    for (int i = f->tamanhoAtual; i < f->capacidadeTotal; i++) {
        enqueue(f, gerarPeca());
    }
}

// -- FUNCOES ESPECIFICAS

// funcao para liberar memoria e encerrar o programa
void finalizarJogo(){
    printf("Finalizando o jogo...\n");
    free(&fila);
    free(&pilha);
    exit(0);
}

// função com código para limpar o terminal/cmd
void limpaTela(){
    printf("\033[2J\033[H");
}

int exibirOpcoesMenu(){
    int opcao = -1;
    
    printf("\n=== Menu ===\n");
    printf("Quantidade de pecas(fila): %d/%d \n", fila.tamanhoAtual, QUANT_MAX_PECAS_FILA);
    printf("Quantidade de pecas(pilha): %d/%d \n", pilha.tamanhoAtual, QUANT_MAX_PECAS_PILHA);
    printf("1. Jogar peça\n");
    printf("2. Reservar peça\n");
    printf("3. Usar peça reservada\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    
    return opcao;
}

void exibirMenu(){
    
    int opcao;
    
    do {
        
        alimentaFila(&fila);
        verPecas(&fila, &pilha);

        opcao = NULL;
        opcao = exibirOpcoesMenu();
        
        limpaTela();
        
        switch(opcao) {

            case 1: {
                jogarPeca(&fila);
                break;
            }
            case 2: {
                reservarPeca(&fila, &pilha);
                break;
            }
            case 3: {
                usarPecaReservada(&pilha);
                break;
            }
            case 0: {
                finalizarJogo();
                break;
            }
            default: printf("Opcao invalida!\n");
        }
        
    } while(opcao != 0);
    
}

// -- FUNCAO PRINCIPAL

int main() {
    
    // inicializa aleatoriedade
    srand(time(NULL)); 

    printf("=== Desafio Tetris Stack – Tema 3 ===\n\n");

    fila = criarFila(QUANT_MAX_PECAS_FILA);
    pilha = criarPilha(QUANT_MAX_PECAS_PILHA);

    exibirMenu();

    free(&fila);
    free(&pilha);
    return 0;
}
