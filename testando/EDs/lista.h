#ifndef LISTA_H
    #define LISTA_H

    #include <stdbool.h>
    #include "item.h"
    
    typedef struct lista_ LISTA;

    LISTA* lista_criar(void);
    void lista_apagar(LISTA** lista);

    bool lista_cheia(LISTA* lista);
    bool lista_vazia(LISTA* lista);
    int lista_tamanho(LISTA* lista);

    bool lista_inserir(LISTA* lista, ITEM* item);
    ITEM* lista_remover(LISTA* lista, int chave);
    ITEM* lista_remover_ultimo(LISTA* lista);

    void lista_set_posicao(LISTA* lista, int pos, ITEM* item);
    ITEM* lista_get_posicao(LISTA* lista, int pos);

    void lista_print(LISTA* lista);
    void lista_limpar(LISTA* lista);
#endif