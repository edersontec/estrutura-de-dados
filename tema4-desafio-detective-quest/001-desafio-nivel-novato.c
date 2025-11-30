#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

Sala* criarSala(const char* nome) {

    //Aloca memória
    Sala* nova = (Sala*) malloc(sizeof(Sala));
    if (!nova) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }

    //atribui valores ao objeto
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

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

// -- FUNCAO PRINCIPAL

void explorarSalas(Sala* atual) {

    char opcao;
    char status[50] = "";
    
    do {

        limpaTela();

        printf("=== Desafio Detective Quest – Tema 4 ===\n");
        printf("\nVocê está na sala: %s\n", atual->nome);

        //Verifica status atual
        printf("%s\n", status);

        // Se não há caminhos, acabou
        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("Você chegou ao fim do caminho. Nenhum outro cômodo disponível.\n");
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
        
    } while(opcao != 's');
    
}

int main() {

    // Criando as salas
    Sala* hall = criarSala("Hall de entrada");
    Sala* salaEstar = criarSala("Sala de estar");
    Sala* cozinha = criarSala("Cozinha");
    Sala* corredor = criarSala("Corredor");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* varanda = criarSala("Varanda");
    Sala* banheiro = criarSala("Banheiro");
    Sala* dispensa = criarSala("Dispensa");
    Sala* quarto = criarSala("Quarto Principal");

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
    explorarSalas(hall);

    return 0;
}
