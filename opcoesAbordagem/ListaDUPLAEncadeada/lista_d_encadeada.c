#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "lista_d_encadeada.h"
#include "item.h"


typedef struct no_{
    ITEM* item;
    NO* anterior;
    NO* proximo;
}NO;

struct lista_{
    int tamanho;
    NO* inicio;
    NO* fim;
    bool ordenada;
};

// Protocolos
bool lista_inserir_busca_ordenada(LISTA* lista, int chave);
bool lista_cheia(LISTA *lista);
LISTA *lista_criar(bool ordenada);
bool lista_vazia(LISTA *lista);
bool lista_inserir(LISTA *lista, ITEM *item);
ITEM *lista_remover(LISTA *lista, int chave);


LISTA *lista_criar(bool ordenada)
{
    LISTA *lista = (LISTA*) malloc(sizeof(LISTA));

    if(lista != NULL){
        lista->fim = lista->inicio = NULL;
        lista->tamanho = 0;
        lista->ordenada = ordenada;

        return lista;   
    }   

    return NULL;
}

bool lista_cheia(LISTA *lista)
{
    if(lista != NULL){
        NO* noaux = (NO*) malloc(sizeof(NO));

        if(noaux != NULL){
            free(noaux);
            return false;
        }
        return true;

    }
    return false;
}

bool lista_vazia(LISTA *lista)
{
    return lista->tamanho ? false : true;
}

bool lista_inserir(LISTA *lista, ITEM *item)
{
    if(!lista_cheia(lista)){
        NO* aux = (NO*) malloc(sizeof(NO));
        aux->item = item;
        if(!lista->ordenada){

            // apenas insere no fim;

            //caso seja o primeiro NO
            if(lista->tamanho == 0){
                lista->inicio = lista->fim = aux;
                // anterior é obrigatorio ser NULL, por que é o primeiro NO
                // o proximo nem tanto
                aux->anterior = aux->proximo = NULL;
                lista->tamanho++;
                return true;
            // caso geral que só insere no fim
            }else{
                lista->fim->proximo = aux;
                aux->anterior = lista->fim;
                lista->fim = aux;
                aux->proximo = NULL;
                lista->tamanho++;
                return true;
            }
        // caso para a lista ordenada
        }else{ 
            int chave = item_get_chave(item);
            lista_inserir_busca_ordenada(lista, chave);
        }
    }
    return false;
}


bool lista_inserir_busca_ordenada(LISTA* lista, int chave)
{
    // caso do inicio
    NO* aux = lista->inicio;
    
    // Nao precisa ser exatamente assim, como foi feito.
    // podiamos, por ser igual, colocar o novo NO no começo direto, assim o fila->inicio->anterior 
    // receberia o aux e o proximo do aux seria o fila->inicio, e seu anteiror igual a nulo. 
    // depois é so colocar o fila->inicio no aux.


    if(chave == item_get_chave(aux->item)){
        NO* aux = (NO*) malloc(sizeof(NO));

        aux->proximo = lista->inicio->proximo;

        // antigo segundo NO da lista, deve apontar como seu anterior para o aux
        lista->inicio->proximo->anterior = aux;

        lista->inicio->proximo = aux;

        aux->anterior = lista->inicio;

        lista->inicio = aux;

        lista->tamanho++;
        return true;
        
    }

    else if(chave == item_get_chave(lista->fim->item)){
        NO* aux = (NO*) malloc(sizeof(NO));

        lista->fim->proximo = aux;
        aux->proximo = NULL;
        aux->anterior = lista->fim;
        lista->fim = aux;
        lista->tamanho++;

        return true;
    }

    NO* noaux;
    while(aux->proximo != NULL){

        if(item_get_chave(aux->proximo->item) > chave){
            NO* noaux = (NO*) malloc(sizeof(NO));
            aux->proximo->anterior = noaux;

            noaux->anterior = aux;
            noaux->proximo = aux->proximo;

            aux->proximo = noaux;

            lista->tamanho++;
            return true;
        }
    }

    return false;
}

ITEM *lista_remover(LISTA *lista, int chave)
{
    if(!lista_vazia(lista)){
        // fazer uma busca sequencial

        NO* aux = lista->inicio;

        if(item_get_chave(aux->item) == chave){
            ITEM *iaux = lista->inicio->item;

            lista->inicio->proximo->anterior = NULL;
            lista->inicio->proximo = NULL;
            free(lista->inicio);
            lista->inicio = lista->inicio->proximo;
            lista->tamanho--;
            return iaux;
        }

        // já chega no penultimo
        while(item_get_chave(aux->proximo->item) != chave){
            aux = aux->proximo;
        }

        // O(1) direto
        if(aux == lista->fim){
            if(item_get_chave(lista->fim->item) == chave){
                ITEM *iAux = lista->fim->item;
                lista->fim->anterior = NULL;
                free(lista->fim);
                aux->proximo = NULL;
                lista->tamanho--;
                return iAux;
            }
        }else{
            // está no meio da lista. e pegamos seu anterior;

            ITEM *iAux = aux->proximo->item;
            
            aux->proximo = aux->proximo->proximo;
            aux->proximo->anterior = NULL;
            aux->proximo->proximo = NULL;

            lista->tamanho--;

            return iAux;

        }


    }
    return NULL;
}