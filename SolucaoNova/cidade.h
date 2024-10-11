#ifndef CIDADE_H
    #define CIDADE_H

    #include <stdbool.h>

    typedef struct estrada_ ESTRADA;
    typedef struct cidade_ CIDADE;

    CIDADE *cidade_criar(int id);
    ESTRADA *estrada_criar(int origem, int distancia);

    bool adicionar_estrada(CIDADE *cidade, int destino, int dist);

    ESTRADA *estrada_proxima(ESTRADA *estrada);
    int estrada_distancia(ESTRADA *estrada);
    int estrada_destino(ESTRADA *estrada);

    ESTRADA *cidade_conexoes(CIDADE *cidade);
    int cidade_id(CIDADE *cidade);

#endif
