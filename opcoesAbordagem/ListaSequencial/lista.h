#ifndef LISTA_H
    #define LISTA_H

    #define TAM 10

    #include "item.h"
    #include <stdbool.h>

    typedef struct lista_ LISTA;

    LISTA *lista_criar(bool ordenada);
    bool lista_cheia(LISTA *lista);

    bool lista_inserir(LISTA *lista, ITEM *item);
    bool lista_vazia(LISTA *lista);

#endif