#ifndef ARESTA_H
    #define ARESTA_H

    typedef struct aresta ARESTA;

    ARESTA* aresta_criar(int cidade_A, int cidade_B, int distancia, int chave);
    int aresta_cidade_a(ARESTA* aresta);
    int aresta_cidade_b(ARESTA* aresta);
    int aresta_distancia(ARESTA* aresta);
    int aresta_get_chave(ARESTA* aresta);
    
#endif