#include "lista.h"
#include "aresta.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct lista_ {
    int inicio;
    int fim;
    int tamanho;
    bool ordenada;
    ARESTA* items[MAX];
};

LISTA* lista_criar(bool ordenada){
    LISTA *lista = (LISTA *) malloc(sizeof(LISTA));

	if(lista != NULL){
		lista->inicio = 0;
		lista->fim = lista->inicio;
        lista->tamanho = 0;
        lista->ordenada = ordenada;
	}

	return lista;
}

void lista_apagar(LISTA** lista){
    return;
}

bool lista_inserir(LISTA* lista, ARESTA* item){
    if((lista != NULL) && (!lista_cheia(lista))){
		(lista->items[lista->fim]) = item;
		lista->fim++;
		lista->tamanho++;
		return true;
	}

	return false;
}



ARESTA* lista_busca(LISTA* lista, int chave){
    int i;

	if(lista != NULL && (!lista_vazia(lista))){
		for(i = 0; i < lista->fim; i++){
			if(aresta_get_chave(lista->items[i]) == chave){
				return lista->items[i];
			}
		}
	}
	return NULL;
}


bool lista_cheia(LISTA* lista) {
    if (lista == NULL) {
        return(true);
    }

    return(lista->tamanho == MAX);
}

bool lista_vazia(LISTA* lista) {
    if (lista == NULL) {
        return(false);
    }

    return(lista->tamanho == 0);
}

int lista_tamanho(LISTA* lista) {
    if (lista == NULL) {
        return(-1);
    }

    return(lista->tamanho);
}

