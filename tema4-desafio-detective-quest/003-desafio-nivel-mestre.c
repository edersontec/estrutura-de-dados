#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h> //para fazer funcao pause

#define QTD_MINIMA_PISTAS_CONSIDERAR_ACUSADO 2
#define TAM_HASH 10

static int contador = 0;

// -- CRIACAO DE STRUCTS

typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

typedef struct NoPista {
    char *valor;
    struct NoPista* esquerda;
    struct NoPista* direita;
} NoPista;
NoPista* raiz;

typedef struct Suspeito {
    char nome[50];
    struct Suspeito *proximo;
} Suspeito;
Suspeito* hashTable[TAM_HASH] = {NULL};

// -- FUNCOES ESPECIFICAS

// funcao para liberar memoria e encerrar o programa
void finalizarJogo(){
    printf("Finalizando o jogo...\n");
    exit(0);
}

// função com código para limpar o terminal/cmd
void limpaTela(){
    printf("\033[2J\033[H");
}

// Função pause
void pause() {
    printf("Pressione qualquer tecla para continuar...\n");
    getch();  // espera o usuário apertar qualquer tecla
}

// -- FUNCOES SUSPEITO

int hash_ponderado(const char* str, int tamanho_tabela) {
        int hash = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            hash += str[i] * (i + 1);
    }
    return hash % tamanho_tabela;
}

void inserirNaHash(const char *nome) {
    unsigned int indice = hash_ponderado(nome, TAM_HASH);

    Suspeito *novo = (Suspeito*) calloc(1, sizeof(Suspeito));
    if (!novo) {
        printf("Erro de alocação!\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->proximo = hashTable[indice];
    hashTable[indice] = novo;
}
 
int encontrarSuspeito(const char *nome) {
    unsigned int indice = hash_ponderado(nome, TAM_HASH);
    int contador = 0;
    Suspeito *atual = hashTable[indice];

    // conta quantas vezes o suspeito foi apontado

    while (atual) {
        if (strcmp(atual->nome, nome) == 0)
           contador++;
        atual = atual->proximo;
    }
    return contador;
}
 
void verificarSuspeitoFinal(const char *nome) {

    // solicitar ao jogador a acusação de um suspeito

    printf("* Obs: %d pistas apontam para o suspeito acusado *\n", QTD_MINIMA_PISTAS_CONSIDERAR_ACUSADO);

    int quantPistas = encontrarSuspeito(nome);
    if (quantPistas >= QTD_MINIMA_PISTAS_CONSIDERAR_ACUSADO)
        printf("Suspeito acusado encontrado: %s\n", nome);
    else
        printf("Suspeito é inocente: %s\n", nome);
    
    printf("* FIM DO JOGO! *\n");
}

// -- FUNCOES PISTA

NoPista* criarNo(const char *str) {
    NoPista* novo = (NoPista*) malloc(sizeof(NoPista));
    if (novo == NULL) {
        printf("[erro]: alocacao de memória!\n");
        exit(1);
    }
    novo->valor = strdup(str);
    novo->esquerda = NULL;
    novo->direita = NULL;
    return novo;
}

NoPista* inserirPista(NoPista *raiz, const char *strPista) {
    if (raiz == NULL) {
        return criarNo(strPista);
    }

    int cmp = strcmp(strPista, raiz->valor);
    if (cmp < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, strPista);
    } else if (cmp > 0) {
        raiz->direita = inserirPista(raiz->direita, strPista);
    } // se cmp == 0, não insere duplicados

    return raiz;
}

void procurarPistas(Sala* sala) {

    printf("Procurando pista na sala...\n");

    if (sala == NULL || sala->pista[0] == '\0') {
        printf("Nenhuma pista na sala.\n");
        return;
    }

    // insere pista na arvore bst
    raiz = inserirPista(raiz, sala->pista);
    printf("* Pista cadastrada: %s\n", sala->pista);

    // insere suspeito relacionado a pista na tabelahash
    char nomeSuspeito[50];
    printf("Analisando o suspeito: A quem pertence a pista '%s'?\nDigite (jardineiro, mordomo ou motorista): ", sala->pista);
    scanf("%49s", nomeSuspeito);

    inserirNaHash(nomeSuspeito);

}

void exibirPistas(NoPista *raiz) {

    // usa recursao para percorrer a arvore bst

    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf(" - %s\n", raiz->valor);
        exibirPistas(raiz->direita);
    }
}

// -- FUNCOES SALA

Sala* criarSala(const char* nome, const char* pista) {

    //Aloca memória
    Sala* nova = (Sala*) calloc(1, sizeof(Sala));
    if (!nova) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    //atribui valores ao objeto
    strcpy(nova->nome, nome);

    // pode ser pista ou nao
    if (pista != NULL) strcpy(nova->pista, pista);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

void explorarSalasComPistas(Sala* atual) {

    limpaTela();

    char opcao;
    char status[50] = "";
    
    do {

        limpaTela();

        printf("=== Desafio Detective Quest – Tema 4 ===\n");
        printf("\nVocê está na sala: %s\n", atual->nome);

        procurarPistas(atual);

        //Verifica status atual
        printf("%s\n", status);

        // Se não há caminhos, acabou
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim do caminho. Nenhum outro cômodo disponível.\n");

            printf("Todas as pistas coletadas (em ordem alfabetica):\n");
            exibirPistas(raiz);

            // Julgamento final

            char nomeSuspeito[50];
            printf("\nJulgamento final: Digite do suspeito que desejar acusar (jardineiro, mordomo ou motorista): ");
            scanf("%49s", nomeSuspeito);
            verificarSuspeitoFinal(nomeSuspeito);

        }else{
            printf("\n");
        }
        
        printf("\n=== Menu ===\n\n");
        printf("Escolha um caminho:\n");
        printf("  e - ir para a esquerda: (%s)\n", atual->esquerda->nome);
        printf("  d - ir para a direita: (%s)\n", atual->direita->nome);
        printf("  s - sair da exploração\n");
        printf("Opção: ");
        scanf(" %c", &opcao);
        
        switch(opcao) {

            case 'e': {
                if (atual->esquerda != NULL){
                    atual = atual->esquerda;
                }else{
                    strcpy(status, "Não há caminho à esquerda!\n");
                }
                break;
            }

            case 'd': {
                if (atual->direita != NULL){
                    atual = atual->direita;
                }else{
                    strcpy(status, "Não há caminho à direita!\n");
                }
            break;
            }

            case 's': finalizarJogo(); break;
            default: printf("Opcao invalida!\n");
        }

        //pause();
        
    } while(opcao != 's');
    
}

int main() {

    // Criando nó raiz
    raiz = NULL;

    // Criando as salas
    Sala* hall = criarSala("Hall de entrada", "Chave do carro");
    Sala* salaEstar = criarSala("Sala de estar", "Revista Super Interessante");
    Sala* cozinha = criarSala("Cozinha", "Colher de ouro");
    Sala* corredor = criarSala("Corredor", NULL);
    Sala* biblioteca = criarSala("Biblioteca", "Papel em branco");
    Sala* varanda = criarSala("Varanda", NULL);
    Sala* banheiro = criarSala("Banheiro", "Escova de dentes");
    Sala* dispensa = criarSala("Dispensa", "Cadeado");
    Sala* quarto = criarSala("Quarto Principal", "Diario");

    //Definindo os nós
    hall->esquerda = salaEstar;
    hall->direita = cozinha;

    salaEstar->esquerda = corredor;
    salaEstar->direita = varanda;

    cozinha->direita = dispensa;
    cozinha->direita = banheiro;
    
    corredor->direita = biblioteca;
    corredor->direita = quarto;

    // Inicia exploração interativa
    explorarSalasComPistas(hall);

    return 0;
}
