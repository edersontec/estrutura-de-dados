#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define QUANT_MAX_COMPONENTES 20 //constante com a quantidade de componentes

int numItensAtual = 0;
bool isVetorOrdenadoPorNome = false;

// Vetor
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;
Componente* componentes;

// -- FUNCOES DE CONTADOR

static int contador = 0;
void resetaContador() { contador = 0; }
void iniciaContador() { resetaContador(); }
void incrementaContador() { contador++; }
int getContador() { return contador; }
void imprimeResultadoContador(){ printf("[contador] Numero de comparações feitas: %d\n", getContador()); }

// -- FUNCAO DE CRONOMETRO

static clock_t inicio, fim;
double medirTempo(void (*algoritmo)(Componente* componentes), Componente* componentes) 
{
    inicio = clock();
    algoritmo(componentes);  // executa o algoritmo
    fim = clock();

    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}


// -- FUNCOES DE ORDENAÇÃO

void bubbleSortNome(Componente* componentes) {
    for (int i = 0; i < numItensAtual - 1; i++) {
        // Após cada passagem, o maior nome "sobe" para o final
        for (int j = 0; j < numItensAtual - 1 - i; j++) {
            
            // strcmp > 0 significa que v[j] vem DEPOIS de v[j+1] (ordem errada)
            if (strcmp(componentes[j].nome, componentes[j + 1].nome) > 0) {
                
                // troca os elementos inteiros (structs)
                Componente temp = componentes[j];
                componentes[j] = componentes[j + 1];
                componentes[j + 1] = temp;
            }

            incrementaContador();
        }
    }
}

void selectionSortPrioridade(Componente* componentes) {
    for (int i = 0; i < numItensAtual - 1; i++) {
        int menor = i;

        for (int j = i + 1; j < numItensAtual; j++) {
            if (componentes[j].prioridade < componentes[menor].prioridade) {
                menor = j;
            }

            incrementaContador();
        }

        // troca o menor encontrado com componentes[i]
        if (menor != i) {
            Componente temp = componentes[i];
            componentes[i] = componentes[menor];
            componentes[menor] = temp;
        }
    }
}

void insertionSortTipo(Componente* componentes) {
    for (int i = 1; i < numItensAtual; i++) {
        Componente chave = componentes[i];
        int j = i - 1;

        while (j >= 0 && strcmp(componentes[j].tipo, chave.tipo) > 0) {
            componentes[j + 1] = componentes[j];
            j--;

            incrementaContador();
        }

        componentes[j + 1] = chave;
    }
}

// -- FUNCOES PARA CRUD VETOR

void mostrarComponentes(Componente* componentes){
    
    printf("\n=== Exibe componentes ===\n\n");
    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Prioridade");
    printf("-------------------------------------------------------------\n");
    
    if(numItensAtual == 0){
        printf("Sua mochila está VAZIA...\n");
        return;
    }
    
    for (int i = 0; i < numItensAtual; i++) {
        printf("%-30s %-20s %-10d\n",
           componentes[i].nome,
           componentes[i].tipo,
           componentes[i].prioridade
        );
    }
    printf("\n");
}

void inserirComponenteVetor(Componente* componentes){
    
    printf("\n=== Inserir componente (vetor) ===\n\n");
    
    // verifica capacidade da mochila
    
    if(numItensAtual >= QUANT_MAX_COMPONENTES){
        printf("Sua mochila está cheia...\n");
        return;
    }
    
    int novoIndice = numItensAtual;
    
    printf("Digite nome do componente (texto): ");
    scanf("%29s", componentes[novoIndice].nome);
    printf("Digite tipo do componente (ex: controle, suporte, propulsão): ");
    scanf("%19s", componentes[novoIndice].tipo);
    do {
        printf("Digite prioridade do componente (numero 0 a 10): ");
        scanf("%d", &componentes[novoIndice].prioridade);
        if (componentes[novoIndice].prioridade < 0 || componentes[novoIndice].prioridade > 10) {
            printf("Valor inválido! Digite um número entre 0 e 10!");
        }
    } while (componentes[novoIndice].prioridade < 0 || componentes[novoIndice].prioridade > 10);
    
    numItensAtual++;

    // mudança na ordem dos elementos pode desordenar vetor,
    // logo setar que ele está desornado
    isVetorOrdenadoPorNome = false;
    
}

int buscaBinariaPorNome(Componente* componentes, char *nomeBusca){

    int pos = -1;

    if (!isVetorOrdenadoPorNome){
        printf("* Busca binário funcionar apenas se o vetor estiver ordenado por 'nome', execute funcao de ordenacao...\n");
        return pos;
    }

    int ini = 0;
    int fim = numItensAtual - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nomeBusca, componentes[meio].nome);

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

void buscarComponenteVetorPorNome(Componente* componentes){
    
    printf("\n=== Busca componente (vetor) ===\n\n");
    
    resetaContador();

    char nomeBusca[30];
    printf("Digite nome do componente (texto): ");
    scanf("%29s", nomeBusca);

    int idxComponenteEncontrado = buscaBinariaPorNome(componentes, nomeBusca);

    if(idxComponenteEncontrado == -1){
        printf("Componente (%s) não foi encontrado\n", nomeBusca);
        return;
    }else{
        printf("\nComponente %d\n", idxComponenteEncontrado + 1);
        printf("Nome: %s\n", componentes[idxComponenteEncontrado].nome);
        printf("Tipo: %s\n", componentes[idxComponenteEncontrado].tipo);
        printf("Prioridade: %d\n", componentes[idxComponenteEncontrado].prioridade);
    }

    imprimeResultadoContador();
    
}

void removerComponenteVetor(Componente* componentes){
    
    printf("\n=== Remover componente (vetor) ===\n\n");
    
    // verifica quantidade de componentes na mochila
    
    if(numItensAtual == 0){
        printf("Sua mochila está VAZIA...\n");
        return;
    }
    
    // procura item
    
    char nomeBusca[30];
    printf("Digite nome do componente (texto) para deletar: ");
    scanf("%29s", nomeBusca);
    
    int idxComponenteEncontrado = buscaBinariaPorNome(componentes, nomeBusca);
    
    // verifica se componente não foi encontrado
    
    if(idxComponenteEncontrado == -1){
        printf("Componente (%s) não foi encontrado\n", nomeBusca);
        return;
    }
    
    // fecha lacuna criada na deleção: coloca componente no final do array para depois remover numItensAtual
    
    Componente tmp;
    tmp = componentes[idxComponenteEncontrado];
    componentes[idxComponenteEncontrado] = componentes[numItensAtual - 1];;
    componentes[numItensAtual - 1] = tmp;
    
    // atualizacao do contador numItensAtual
    
    numItensAtual--;

    // mudança na ordem dos elementos pode desordenar vetor,
    // logo setar que ele está desornado
    isVetorOrdenadoPorNome = false;

    printf("Componente (%s) foi removido\n", nomeBusca);
    
}

void ordenarComponenteVetor(Componente* componentes) {
    
    int opcao;
    printf("\n=== Ordenar vetor ===\n\n");
    printf("Selecione estrategia de ordenação:\n");
    printf("1. Por nome\n");
    printf("2. Por Tipo\n");
    printf("3. Por Prioridade\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    resetaContador();

    switch(opcao) {
            case 1: {
                double tempo = medirTempo(bubbleSortNome, componentes);
                printf("[tempo] %.6f segundos\n", tempo);

                isVetorOrdenadoPorNome = true;
                break;
            }
            case 2: {
                double tempo = medirTempo(insertionSortTipo, componentes);
                printf("[tempo] %.6f segundos\n", tempo);

                isVetorOrdenadoPorNome = false;
                break;
            }
            case 3: {
                double tempo = medirTempo(selectionSortPrioridade, componentes);
                printf("[tempo] %.6f segundos\n", tempo);

                isVetorOrdenadoPorNome = false;
                break;
            }
            default: printf("Opcao invalida!\n");
        }

        imprimeResultadoContador();
    
}

// -- FUNCOES ESPECIFICAS

// funcao para liberar memoria e encerrar o programa
void finalizarJogo(){
    printf("Finalizando o jogo...\n");
    free(componentes);
    exit(0);
}

// função com código para limpar o terminal/cmd
void limpaTela(){
    printf("\033[2J\033[H");
}

int exibirOpcoesMenu(){
    int opcao = -1;
    
    printf("\n=== Menu ===\n\n");
    printf("Itens na mochila: %d/%d \n", numItensAtual, QUANT_MAX_COMPONENTES);
    printf("1. Adicionar componente\n");
    printf("2. Remover componente\n");
    printf("3. Lista componentes na mochila\n");
    printf("4. Buscar componente (por nome)\n");
    printf("5. Ordenar componentes na mochila\n");
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
            case 1: inserirComponenteVetor(componentes); break;
            case 2: removerComponenteVetor(componentes); break;
            case 3: mostrarComponentes(componentes); break;
            case 4: buscarComponenteVetorPorNome(componentes); break;
            case 5: ordenarComponenteVetor(componentes); break;
            case 6: finalizarJogo(); break;
            default: printf("Opcao invalida!\n");
        }
        
    } while(opcao != 6);
    
}

// -- FUNCAO PRINCIPAL

int main() {
    
    printf("=== Desafio Free Fire - Tema 2 ===\n");
    printf("=== Mochila de Componentes ===\n");
    
    componentes = (Componente*) calloc(QUANT_MAX_COMPONENTES, sizeof(Componente));

    exibirMenuVetor();

    free(componentes);
    return 0;
}
