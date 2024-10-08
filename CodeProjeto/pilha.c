#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pilha.h"
#include "item.h"

// Protocolos das funções
PILHA* pilha_criar(void);
void pilha_apagar(PILHA** pilha);
bool pilha_vazia(PILHA* pilha);
bool pilha_cheia(PILHA* pilha);
int pilha_tamanho(PILHA* pilha);
ITEM* pilha_topo(PILHA* pilha);
bool pilha_empilhar(PILHA* pilha, ITEM* item);
ITEM* pilha_desempilhar(PILHA* pilha);

void pilha_limpar(PILHA *pilha);

void pilha_print(PILHA* pilha);
void pilha_inverter(PILHA* pilha);

// Cria a pilha
// veja que é uma passagem do tipo void, pois
// não importa o que está sendo passado, o tipo
// de pilha que será dado, ela apenas reservará espaço
// na heap, como esperado de uma pilha
PILHA* pilha_criar(void) {
    PILHA* pilha = (PILHA*)malloc(sizeof(PILHA));

    if (pilha != NULL) {
        pilha->tamanho = 0;
    }

    return pilha;
}

// Retorna se a pilha está vázia ou não
bool pilha_vazia(PILHA* pilha) {
    if (pilha != NULL) {
        return ((pilha->tamanho == 0) ? true : false);
    }
    return false;
}

// Retorna se a pilha está cheia ou não
// e isso se dá pelo tamanho dá pilha, que é um contador
// de general scope ser igual ao tamanho pré-definido total
bool pilha_cheia(PILHA* pilha) {
    if (pilha != NULL) {
        return ((pilha->tamanho == TAM) ? true : false);
    }
    return false;
}

// Retorna o tamanho da pilha
// if de uma linha " != NULL " 
int pilha_tamanho(PILHA* pilha) {
    return ((pilha != NULL) ? pilha->tamanho : -1);
}

// Particularidade: a pilha retornará se o item foi
// colocado ou não, com os respectivos, true ou false;
bool pilha_empilhar(PILHA* pilha, ITEM* item) {
    if (!pilha_cheia(pilha)) {
        pilha->item[pilha->tamanho] = item;
        pilha->tamanho++;
        return true;
    }
    return false;
}

// Aqui, como na torre de hanoi, apenas o topo poderá 
// ser retirado. Assim, para complementar o código
// quando retirado o item, ele será mostrado ao usuário final
ITEM* pilha_desempilhar(PILHA* pilha) {
    ITEM *iaux;
    // Perceba que aqui, o item não é retirado da memória,
    // ele ainda ocupa um pedaço dela e é deixado para o usuário
    // final decidir se irá retirá-lo ou não.
    if(!pilha_vazia(pilha)){
        iaux  = pilha_topo(pilha);
        pilha->item[pilha->tamanho-1] = NULL;
        pilha->tamanho--;
        return iaux;
    }
    return NULL;
}

// Função para retornar o item que está no topo, que é
// o tamanho - 1
ITEM* pilha_topo(PILHA* pilha){
    return (!pilha_vazia(pilha)) ? pilha->item[pilha->tamanho - 1] : NULL;
}

// Função para apagar toda a pilha
void pilha_apagar(PILHA **pilha){
    while(!pilha_vazia(*pilha)){
        pilha_desempilhar(*pilha);
    }

    free(*pilha);
    *pilha = NULL;
}


void pilha_print(PILHA *pilha){
    for(int i=0; i < pilha->tamanho; i++){
        if(i == pilha->tamanho - 1)
            printf("%d", item_get_chave(pilha->item[i]));
        
        printf("%d - ", item_get_chave(pilha->item[i]));
    }
}

void pilha_limpar(PILHA *pilha){
    if(pilha == NULL){
        return;
    }
    for(int i=0; i < pilha->tamanho; i++){
        item_apagar(&(pilha->item[i]));
        free(pilha->item[i]);
    }

    pilha->tamanho=0;
}