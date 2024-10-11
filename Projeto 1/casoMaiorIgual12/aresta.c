#include "aresta.h"
#include <stdio.h>
#include <stdlib.h>

struct aresta{
    int cidade_A;
    int cidade_B;
    int distancia;
    int chave;
};

ARESTA* aresta_criar(int cidade_A, int cidade_B, int distancia, int chave){
    ARESTA* aresta = (ARESTA*) malloc(sizeof(ARESTA));

    if(aresta != NULL){
        aresta->cidade_A = cidade_A;
        aresta->cidade_B = cidade_B;
        aresta->distancia = distancia;
        aresta->chave = chave;
    }
    
    return aresta;
}

int aresta_cidade_a(ARESTA* aresta){
    return aresta->cidade_A;
}

int aresta_cidade_b(ARESTA* aresta){
    return aresta->cidade_B;
}

int aresta_distancia(ARESTA* aresta){
    return aresta->distancia;
}

int aresta_get_chave(ARESTA* aresta){
    return aresta->chave;
}