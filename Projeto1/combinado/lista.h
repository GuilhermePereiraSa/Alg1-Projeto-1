#ifndef LISTA_H
    #define LISTA_H
    #define MAX 200

    #include <stdbool.h>
    #include "aresta.h"

    typedef struct lista_ LISTA;

    LISTA* lista_criar(bool ordenada);
    void lista_apagar(LISTA** lista);

    bool lista_inserir(LISTA* lista, ARESTA* item);

    ARESTA* lista_busca(LISTA* lista, int chave);

    int lista_tamanho(LISTA* lista);
    bool lista_cheia(LISTA* lista);
    bool lista_vazia(LISTA* lista);

#endif



    