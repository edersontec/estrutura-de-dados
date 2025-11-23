#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define QUANT_MAX_ITENS_MOCHILA 10 //constante com a quantidade de itens na mochila

// criação de struct Item com 3 itens - Structs agrupa variáveis diferentes para oganizar o código;

int numItensAtual = 0;
bool isVetorOrdenado = false;

// Vetor
typedef struct {
    char nome[30];
    char tipo[20];
    int quant;
} Item;
Item* itens;

// Lista
typedef struct No {
    char nome[30];
    char tipo[20];
    int quant;
    struct No* proximo;
} No;
No* nos;

// -- FUNCOES DE CONTADOR

static int contador = 0;
void iniciaContador() { contador = 0; }
void incrementaContador() { contador++; }
void resetaContador() { contador = 0; }
int getContador() { return contador; }

// -- FUNCOES PARA CRUD VETOR

void listarItemVetor(Item* itens){
    
    printf("\n=== Exibe itens (vetor) ===\n");
    
    if(numItensAtual == 0){
        printf("Sua mochila está VAZIA...\n");
        return;
    }
    
    for (int i = 0; i < numItensAtual; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", itens[i].nome);
        printf("tipo: %s\n", itens[i].tipo);
        printf("Quantidade: %d\n", itens[i].quant);
    }
    printf("\n");
}

void inserirItemVetor(Item* itens){
    
    printf("\n=== Inserir item (vetor) ===\n");
    
    // verifica capacidade da mochila
    
    if(numItensAtual >= QUANT_MAX_ITENS_MOCHILA){
        printf("Sua mochila está cheia...\n");
        return;
    }
    
    int novoIndice = numItensAtual;
    
    printf("Digite nome do item (texto): ");
    scanf("%29s", itens[novoIndice].nome);
    printf("Digite tipo do item (ex: arma, munição e cura): ");
    scanf("%19s", itens[novoIndice].tipo);
    printf("Digite quantidade do item (numero): ");
    scanf("%d", &itens[novoIndice].quant);
    
    numItensAtual++;

    // mudança na ordem dos elementos pode desordenar vetor,
    // logo setar que ele está desornado
    isVetorOrdenado = false;
    
}

int buscarSequencialItemVetor(Item* itens, char *nomeBusca){
    
    int pos = -1;
    
    for (int i = 0; i < numItensAtual; i++) {
        if( strcmp(itens[i].nome, nomeBusca) == 0 ){
            // encontrado item procurado
            pos = i;
            return pos;
        }

        incrementaContador();
    }
    
    return pos;
}

int buscarBinariaItemVetor(Item* itens, char *nomeBusca){

    int pos = -1;

    if (!isVetorOrdenado){
        printf("* Busca binário funcionar apenas se o vetor estiver ordenado, execute funcao de ordenacao...\n");
        return pos;
    }

    int ini = 0;
    int fim = numItensAtual - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nomeBusca, itens[meio].nome);

        if (cmp == 0) {
            pos = meio; // encontrado!
            return pos;
        } 
        else if (cmp > 0) {
            ini = meio + 1;  // procura na metade direita
        } 
        else {
            fim = meio - 1;  // procura na metade esquerda
        }

        incrementaContador();
    }

    return pos;

}

void buscarItemVetor(Item* itens){
    
    printf("\n=== Busca item (vetor) ===\n");
    
    resetaContador();

    char nomeBusca[30];
    printf("Digite nome do item (texto): ");
    scanf("%29s", nomeBusca);

    int opcaoBusca;
    printf("Selecione tipo de busca\n");
    printf("1. Sequencial\n");
    printf("2. Binaria\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcaoBusca);

    int idxItemEncontrado;
    switch(opcaoBusca) {
        case 1: idxItemEncontrado = buscarSequencialItemVetor(itens, nomeBusca); break;
        case 2: idxItemEncontrado = buscarBinariaItemVetor(itens, nomeBusca); break;
        default: printf("Opcao invalida!\n");
    }

    if(idxItemEncontrado == -1){
        printf("Item (%s) não foi encontrado\n", nomeBusca);
        return;
    }else{
        printf("\nItem %d\n", idxItemEncontrado + 1);
        printf("Nome: %s\n", itens[idxItemEncontrado].nome);
        printf("tipo: %s\n", itens[idxItemEncontrado].tipo);
        printf("Quantidade: %d\n", itens[idxItemEncontrado].quant);
    }

    printf("Numero de comparações feitas: %d\n", getContador());
    
}

void removerItemVetor(Item* itens){
    
    printf("\n=== Remover item (vetor) ===\n");
    
    // verifica quantidade de itens na mochila
    
    if(numItensAtual == 0){
        printf("Sua mochila está VAZIA...\n");
        return;
    }
    
    // procura item
    
    char nomeBusca[30];
    printf("Digite nome do item (texto) para deletar: ");
    scanf("%29s", nomeBusca);
    
    int idxItemEncontrado = buscarSequencialItemVetor(itens, nomeBusca);
    
    // verifica se item não foi encontrado
    
    if(idxItemEncontrado == -1){
        printf("Item (%s) não foi encontrado\n", nomeBusca);
        return;
    }
    
    // fecha lacuna criada na deleção: coloca item no final do array para depois remover numItensAtual
    
    Item tmp;
    tmp = itens[idxItemEncontrado];
    itens[idxItemEncontrado] = itens[numItensAtual - 1];;
    itens[numItensAtual - 1] = tmp;
    
    // atualizacao do contador numItensAtual
    
    numItensAtual--;

    // mudança na ordem dos elementos pode desordenar vetor,
    // logo setar que ele está desornado
    isVetorOrdenado = false;

    printf("Item (%s) foi removido\n", nomeBusca);
    
}

void ordenarVetorPorNome(Item* itens) {
    
    printf("\n=== Ordenar vetor por nome (vetor) ===\n");
    
    // ordenar por bubble sort
    
    for (int i = 0; i < numItensAtual - 1; i++) {
        for (int indiceAtual = 0; indiceAtual < numItensAtual - i - 1; indiceAtual++) {
            int proximoIndice = indiceAtual + 1;
            
            // Se o nome atual está alfabeticamente depois do próximo
            if (strcmp(itens[indiceAtual].nome, itens[proximoIndice].nome) > 0) {
                
                printf("-> (%s) trocado de lugar com (%s)\n", itens[indiceAtual].nome, itens[proximoIndice].nome);
                
                // Troca os dois itens de posição
                Item temporario = itens[indiceAtual];
                itens[indiceAtual] = itens[proximoIndice];
                itens[proximoIndice] = temporario;
            }
        }
    }

    isVetorOrdenado = true;
}

// -- FUNCOES PARA CRUD LISTA

void listarItemLista(No* nos){
    
    printf("\n=== Exibe itens (lista) ===\n");
    
    if(numItensAtual == 0){
        printf("Sua mochila está VAZIA...\n");
        return;
    }
    
    int idxItem = 0;
    No* atual = &nos[0];
    
    // Percorrendo a lista
    while (atual != NULL) {
        printf("\nItem %d\n", idxItem + 1);
        printf("Nome: %s\n", atual->nome);
        printf("Tipo: %s\n", atual->tipo);
        printf("Quantidade: %d\n", atual->quant);
        
        atual = atual->proximo;
        idxItem++;
    }
    
    printf("\n");
}

void inserirItemLista(No* nos){
    
    printf("\n=== Inserir item (lista) ===\n");
    
    // verifica capacidade da mochila
    
    if(numItensAtual >= QUANT_MAX_ITENS_MOCHILA){
        printf("Sua mochila está cheia...\n");
        return;
    }
    
    int novoIndice = numItensAtual;
    
    printf("Digite nome do item (texto): ");
    scanf("%29s", nos[novoIndice].nome);
    printf("Digite tipo do item (ex: arma, munição e cura): ");
    scanf("%19s", nos[novoIndice].tipo);
    printf("Digite quantidade do item (numero): ");
    scanf("%d", &nos[novoIndice].quant);
    
    // Problema: o exercicio sugere adicionar o ponteiro para o "proximo" item,
    // porém como a lista está sendo preeenchida via input do usuário ao poucos,
    // haverá um problema de apontar para o proximo "No" que ainda não foi preenchido.
    // Apontar para o "proximo" só tem sentido se toda a lista encadeada já estiver preenchida.
    // Sendo assim, penso que nunca se deve apontar para itens que "não existem" ainda.
    
    // Solução 1: Verificar se no No atual existe dados, como "nome" por exemplo.
    // Solução 2: fazer igual aos commits do git, ao invés de apontar para o próximo "No",
    // apontar para "No" anterior/"parent"
    // Solução 3: atualizar o "No" anterior para incluir ponteiro para o novo "No" criado
    
    if (numItensAtual == 0) {
        nos[0].proximo = NULL; // primeiro item
    } else {
        nos[numItensAtual - 1].proximo = &nos[numItensAtual]; // aponta o ultimo para o novo
        nos[numItensAtual].proximo = NULL; // novo último item
    }
    
    numItensAtual++;
}

int buscarSequencialItemLista(No* nos, char *nomeBusca){
    
    int pos = -1;
    
    int idxItem = 0;
    No* atual = &nos[0];
    
    // Percorrendo a lista
    while (atual != NULL) {
        if( strcmp(atual->nome, nomeBusca) == 0 ){
            // encontrado item procurado
            pos = idxItem;
            return pos;
        }
        atual = atual->proximo;
        idxItem++;
    }
    
    return pos;
}

int buscarBinariaItemLista(No* nos, char *nomeBusca){
    printf("TODO - implementar");
    return -1;
}

void buscarItemLista(No* nos){
    
    printf("\n=== Busca item (lista) ===\n");
    
    char nomeBusca[30];
    printf("Digite nome do item (texto): ");
    scanf("%29s", nomeBusca);
    
    int idxItemEncontrado = buscarSequencialItemLista(nos, nomeBusca);
    if(idxItemEncontrado == -1){
        printf("Item (%s) não foi encontrado\n", nomeBusca);
        return;
    }else{
        printf("\nItem %d\n", idxItemEncontrado + 1);
        printf("Nome: %s\n", nos[idxItemEncontrado].nome);
        printf("tipo: %s\n", nos[idxItemEncontrado].tipo);
        printf("Quantidade: %d\n", nos[idxItemEncontrado].quant);
        printf("id.memoria do proximo No da lista: %d\n", nos[idxItemEncontrado].proximo);
    }
}

void removerItemLista(No* nos){
    
    printf("\n=== Remover item (lista) ===\n");
    
    // verifica quantidade de itens na mochila
    
    if(numItensAtual == 0){
        printf("Sua mochila está VAZIA...\n");
        return;
    }
    
    // procura item
    
    char nomeBusca[30];
    printf("Digite nome do item (texto) para deletar: ");
    scanf("%29s", nomeBusca);
    
    int idxItemEncontrado = buscarSequencialItemLista(nos, nomeBusca);
    
    // verifica se item não foi encontrado
    
    if(idxItemEncontrado == -1){
        printf("Item (%s) não foi encontrado\n", nomeBusca);
        return;
    }
    
    // Se não for o primeiro nó, ajusta o ponteiro do anterior
    if (idxItemEncontrado > 0) {
        nos[idxItemEncontrado - 1].proximo = nos[idxItemEncontrado].proximo;
    }
    
    // Observacao: se for o primeiro nó, apenas ajustamos o início da lista,
    // porque o primeiro nó sempre é &nos[0], então não precisa mudar nada
    
    // Se for o último item, não precisa alterar ponteiros extras
    // A lista termina em NULL automaticamente porque o último nó já tem proximo = NULL
    
    // "Removendo" o item do vetor: movemos os itens subsequentes para frente
    for (int i = idxItemEncontrado; i < numItensAtual - 1; i++) {
        nos[i] = nos[i + 1];  // copia o próximo nó para este
        // ajusta o ponteiro do novo nó para o próximo correto
        if (i < numItensAtual - 2) {
            nos[i].proximo = &nos[i + 1];
        } else {
            nos[i].proximo = NULL;
        }
    }
    
    // atualizacao do contador numItensAtual
    numItensAtual--;
    printf("Item (%s) foi removido\n", nomeBusca);
    
}

void ordenarListaPorNome(No* nos) {
    if (!nos || numItensAtual < 2) return;
    
    No* atual = &nos[0];
    
    while (atual->proximo != NULL) {
        if (strcmp(atual->nome, atual->proximo->nome) > 0) {
            
            printf("-> (%s) trocado de lugar com (%s)\n", atual->nome, atual->proximo->nome);
            
            No* prox = atual->proximo;
            
            char nomeTemp[30], tipoTemp[20];
            int quantTemp;
            
            // troca nome
            strcpy(nomeTemp, atual->nome);
            strcpy(atual->nome, prox->nome);
            strcpy(prox->nome, nomeTemp);
            
            // troca tipo
            strcpy(tipoTemp, atual->tipo);
            strcpy(atual->tipo, prox->tipo);
            strcpy(prox->tipo, tipoTemp);
            
            // troca quantidade
            quantTemp = atual->quant;
            atual->quant = prox->quant;
            prox->quant = quantTemp;
            
        }
        atual = atual->proximo;
    }
}


// -- FUNCOES ESPECIFICAS

// funcao para liberar memoria e encerrar o programa
void finalizarJogo(){
    printf("Finalizando o jogo...\n");
    free(itens);
    exit(0);
}

// função com código para limpar o terminal/cmd
void limpaTela(){
    printf("\033[2J\033[H");
}

int exibirOpcoesMenu(){
    int opcao = -1;
    
    printf("\n=== Menu ===\n");
    printf("Itens na mochila: %d/%d \n", numItensAtual, QUANT_MAX_ITENS_MOCHILA);
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Lista itens na mochila\n");
    printf("4. Buscar item por nome\n");
    printf("5. Ordenar itens na mochila\n");
    printf("6. Finalizar\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);
    
    return opcao;
}

void exibirMenuVetor(){
    
    int opcao;
    
    do {
        
        opcao = NULL;
        opcao = exibirOpcoesMenu();
        
        limpaTela();
        
        switch(opcao) {
            case 1: inserirItemVetor(itens); break;
            case 2: removerItemVetor(itens); break;
            case 3: listarItemVetor(itens); break;
            case 4: buscarItemVetor(itens); break;
            case 5: ordenarVetorPorNome(itens); break;
            case 6: finalizarJogo(); break;
            default: printf("Opcao invalida!\n");
        }
        
    } while(opcao != 6);
    
}

void exibirMenuLista(){
    
    int opcao;
    
    do {
        
        opcao = NULL;
        opcao = exibirOpcoesMenu();
        
        limpaTela();
        
        switch(opcao) {
            case 1: inserirItemLista(nos); break;
            case 2: removerItemLista(nos); break;
            case 3: listarItemLista(nos); break;
            case 4: buscarItemLista(nos); break;
            case 5: ordenarListaPorNome(nos); break;
            case 6: finalizarJogo(); break;
            default: printf("Opcao invalida!\n");
        }
        
    } while(opcao != 6);
    
}

// -- FUNCAO PRINCIPAL

int main() {
    
    printf("=== Desafio Free Fire - Tema 2 ===\n");
    printf("=== Mochila de sobrevivencia ===\n");
    
    //itens = (Item*) malloc(QUANT_MAX_ITENS_MOCHILA * numItensAtual);
    //nos = (No*) malloc(QUANT_MAX_ITENS_MOCHILA * numItensAtual);
    itens = (Item*) calloc(QUANT_MAX_ITENS_MOCHILA, sizeof(Item));
    nos = (No*) calloc(QUANT_MAX_ITENS_MOCHILA, sizeof(No));
    

    int opcaoEstrutura;
    printf("Selecione tipo de estrutura utilizar:\n");
    printf("1. Vetor sequencial\n");
    printf("2. Lista encadeada\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcaoEstrutura);

    int idxItemEncontrado;
    switch(opcaoEstrutura) {
        case 1: exibirMenuVetor(); break;
        case 2: exibirMenuLista(); break;
        default: printf("Opcao invalida!\n");
    }
    
    free(itens);
    return 0;
}
