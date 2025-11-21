#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUANT_MAX_ITENS_MOCHILA 10 //constante com a quantidade de itens na mochila

// criação de struct Item com 3 itens - Structs agrupa variáveis diferentes para oganizar o código;

typedef struct {
    char nome[30];
    char tipo[20];
    int quant;
} Item;

Item* itens;
int numItens = 0;

// -- FUNCOES PARA CRUD

int listarItens(Item* itens){

    if(numItens == 0){
        printf("Sua mochila está VAZIA...\n");
        return 0;
    }
    
    for (int i = 0; i < numItens; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", itens[i].nome);
        printf("tipo: %s\n", itens[i].tipo);
        printf("Quantidade: %d\n", itens[i].quant);
    }
    printf("\n");

    return 0;
}

int inserirItem(Item* itens){

    printf("\n=== Inserir item ===\n");
    
    // verifica capacidade da mochila

    if(numItens >= QUANT_MAX_ITENS_MOCHILA){
        printf("Sua mochila está cheia...\n");
        return 0;
    }

    listarItens(itens);

    int novoIndice = numItens;

    printf("Digite nome do item (texto): ");
    scanf("%29s", itens[novoIndice].nome);
    printf("Digite tipo do item (ex: arma, munição e cura): ");
    scanf("%19s", itens[novoIndice].tipo);
    printf("Digite quantidade do item (numero): ");
    scanf("%d", &itens[novoIndice].quant);

    numItens++;

    return 0;
}

int buscarItem(Item* itens, char *nomeBusca){
    
    int pos = -1;
    
    for (int i = 0; i < numItens; i++) {
        if( strcmp(itens[i].nome, nomeBusca) == 0 ){
            // encontrado item procurado
            pos = i;
            return pos;
        }
    }

    return pos;
}

int removerItem(Item* itens){

    printf("\n=== Remover item ===\n");

    // verifica quantidade de itens na mochila

    if(numItens == 0){
        printf("Sua mochila está VAZIA...\n");
        return 0;
    }

    // procura item

    char nomeBusca[30];
    printf("Digite nome do item (texto) para deletar: ");
    scanf("%29s", nomeBusca);

    int idxItemEncontrado = buscarItem(itens, nomeBusca);

    // verifica se item não foi encontrado

    if(idxItemEncontrado == -1){
        printf("Item (%s) não foi encontrado\n", nomeBusca);
        return 0;
    }

    // fecha lacuna criada na deleção: coloca item no final do array para depois remover numItens
    
    Item tmp;
    tmp = itens[idxItemEncontrado];
    itens[idxItemEncontrado] = itens[numItens - 1];;
    itens[numItens - 1] = tmp;

    // atualizacao do contador numItens

    numItens--;
    printf("Item (%s) foi removido\n", nomeBusca);
    
    return 0;
}

// -- FUNCOES ESPECIFICAS

// funcao para liberar memoria e encerrar o programa
int finalizarJogo(){
    printf("Finalizando o jogo...\n");
    free(itens);
    exit(0);
}

// função com código para limpar o terminal/cmd
void limpaTela(){
    printf("\033[2J\033[H");
}

int exibirMenu(){

    int opcao;
    
    do {
        printf("\n=== Menu ===\n");
        printf("Itens na mochila: %d/%d \n", numItens, QUANT_MAX_ITENS_MOCHILA);
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Lista itens na mochila\n");
        printf("4. Finalizar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            
            case 1: {
                limpaTela();
                inserirItem(itens);

                break;
            }
            
            case 2: {
                limpaTela();
                removerItem(itens);

                break;
            }
            
            case 3: {
                limpaTela();
                printf("\n=== Exibe itens ===\n");
                listarItens(itens);
                break;
            }
            
            case 4: {
                limpaTela();
                finalizarJogo();
                break;
            }
            
            default:
            printf("Opcao invalida!\n");
        }
        
    } while(opcao != 4);

    return 0;

}

// -- FUNCAO PRINCIPAL

int main() {

    printf("=== Desafio Free Fire - Tema 2 ===\n");
    printf("=== Mochila de sobrevivencia ===\n");

    itens = (Item*) malloc(QUANT_MAX_ITENS_MOCHILA * numItens);

    exibirMenu();

    free(itens);
    return 0;
}
