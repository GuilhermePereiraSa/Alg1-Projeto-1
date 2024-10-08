#include <stdlib.h>
#include <stdio.h>
#include "item.h"

typedef struct item_{ 
    int chave;   //indexador
    void *dados; //ponteiro para o dado
} ITEM;

ITEM *item_criar (int chave, void *dado){
    ITEM *item = (ITEM *) malloc(sizeof(ITEM));
           
    if (item != NULL){
        item->chave = chave;
        item->dados = dado;
    }
    return(item);
}

bool item_apagar(ITEM **item){
	if (*item == NULL) {
		return(false);
	}

    free (*item);
    *item = NULL; 
    return(true);
}

int item_get_chave(ITEM *item){
    if (item == NULL) {
		exit(1);
	}

    return(item->chave);
}


bool item_set_chave(ITEM *item, int chave){
	if (item == NULL) {
		return(false);
	}

    item->chave = chave;
    return (true);
}

void *item_get_dados(ITEM *item){
	if (item == NULL) {
		return(NULL);
	}
	return(item->dados);
}
