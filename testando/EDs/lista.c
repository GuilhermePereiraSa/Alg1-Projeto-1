#define TAM_MAX 100

#include "item.h"
#include "lista.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct lista_ {
    int tamanho;
    ITEM* items[TAM_MAX];
};

/*
Cria uma lista sequencial alocando a memória necessária.
Se a lista existe (não nula), seu tamanho é iniciado com 0.
A lista é retornada.
*/
LISTA* lista_criar(void) {
    LISTA* lista = (LISTA*) malloc(sizeof(LISTA));

    if (lista != NULL) {
        lista->tamanho = 0;
    }

    return(lista);
}

/*
Apaga a lista da memória, excluindo também seus items.
*/
void lista_apagar(LISTA** lista) {
    if (*lista == NULL) {
        return;
    }

    for (int i = 0; i < (*lista)->tamanho; i++) {
        item_apagar(&(*lista)->items[i]);
    }

    free(*lista);
    *lista = NULL;
}

/*
Verifica se a lista está cheia.
Caso a lista seja nula, true é retornado.
*/
bool lista_cheia(LISTA* lista) {
    if (lista == NULL) {
        return(true);
    }

    return(lista->tamanho == TAM_MAX);
}

/*
Verifica se a lista está vazia.
Caso a lista seja nula, false é retornado.
*/
bool lista_vazia(LISTA* lista) {
    if (lista == NULL) {
        return(false);
    }

    return(lista->tamanho == 0);
}

/*
Retorna o tamanho da lista.
Caso a lista seja nula, -1 é retornado.
*/
int lista_tamanho(LISTA* lista) {
    if (lista == NULL) {
        return(-1);
    }

    return(lista->tamanho);
}

/*
Insere um item no fim da lista.
*/
bool lista_inserir(LISTA* lista, ITEM* item) {
    if (lista_cheia(lista)) {
        return(false);
    }
    
    lista->items[lista->tamanho] = item;
    lista->tamanho++;

    return(true);
}

/*
Remove um item dada sua chave.
*/
ITEM* lista_remover(LISTA* lista, int chave) {
    return(NULL);
}

/*
Remove o ultimo item da lista.
*/
ITEM* lista_remover_ultimo(LISTA* lista) {
    if (lista_vazia(lista)) {
        return(NULL);
    }

    lista->tamanho--;
    ITEM* item = lista->items[lista->tamanho];
    lista->items[lista->tamanho] = NULL;

    return(item);
}

/*
Coloca um item numa posição especificada.
*/
void lista_set_posicao(LISTA* lista, int pos, ITEM* item) {
    if (pos >= TAM_MAX) {
        return;
    }

    //verifica se há um item nessa posição
    if (lista->items[pos] != NULL) {
        item_apagar(&lista->items[pos]);
    }

    //o tamanho não será aumentado!
    lista->items[pos] = item;
}

/*
Pega um item de uma posição especifica.
*/
ITEM* lista_get_posicao(LISTA* lista, int pos) {
    if (lista_vazia(lista) || pos >= TAM_MAX) {
        return(NULL);
    }

    return(lista->items[pos]);
}

/*
Exibe a lista.
*/
void lista_print(LISTA* lista) {
    if (lista_vazia(lista)) {
        return;
    }

    for (int i = 0; i < lista->tamanho; i++) {
        printf("%d\n", item_get_chave(lista->items[i]));
    }
}

/*
Apaga todos os items da lista e zera o tamanho
*/
void lista_limpar(LISTA* lista) {
    if (lista_vazia(lista)) {
        return;
    }

    for (int i = 0; i < lista->tamanho; i++) {
        item_apagar(&lista->items[i]);
    }

    lista->tamanho = 0;
}