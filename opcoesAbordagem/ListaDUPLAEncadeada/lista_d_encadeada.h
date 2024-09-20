#ifndef LISTA_D_ENCADEADA
    #define LISTA_D_ENCADEADA
    
    #include <stdbool.h>
    #include "item.h"

    typedef struct lista_ LISTA;

    LISTA *lista_criar(bool ordenada);

    ITEM *lista_remover(LISTA *lista, int chave);

    bool lista_inserir(LISTA *lista, ITEM *item);


#endif