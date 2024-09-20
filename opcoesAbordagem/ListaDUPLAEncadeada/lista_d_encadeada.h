#ifndef LISTA_D_ENCADEADA
    #define LISTA_D_ENCADEADA
    
    #include <stdbool.h>
    #include "item.h"

    typedef struct lista_ LISTA;
    typedef struct no_ NO;

    bool lista_cheia(LISTA *lista);
    LISTA *lista_criar(bool ordenada);
    bool lista_vazia(LISTA *lista);
    bool lista_inserir(LISTA *lista, ITEM *item);
    ITEM *lista_remover(LISTA *lista, int chave);


#endif