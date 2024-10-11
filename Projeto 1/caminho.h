#ifndef CAMINHO_H
    #define CAMINHO_H

    #include <stdbool.h>

    typedef struct caminho CAMINHO;

    CAMINHO* caminho_inicializa(int custo, int percurso[], int tamanho);
    int* caminho_get_percurso(CAMINHO* caminho);
    int caminho_get_custo(CAMINHO* caminho);
    void caminho_set_percurso(CAMINHO* caminho, int percurso[], int tamanho);
    void caminho_set_custo(CAMINHO* caminho, int custo);
#endif
    