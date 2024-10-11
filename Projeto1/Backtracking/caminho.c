#include "caminho.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct caminho{
	int* percurso;
	int custo;
};

CAMINHO* caminho_inicializa(int custo, int percurso[], int tamanho){
    CAMINHO* caminho = (CAMINHO*) malloc(sizeof(CAMINHO));
    caminho->custo = custo;
    caminho->percurso = (int*) malloc(tamanho * sizeof(int));
    memcpy(caminho->percurso, percurso, tamanho * sizeof(int));
    return caminho;   
}

int* caminho_get_percurso(CAMINHO* caminho){
    return caminho->percurso;
}

int caminho_get_custo(CAMINHO* caminho){
    return caminho->custo;
}

void caminho_set_percurso(CAMINHO* caminho, int percurso[], int tamanho){
    for (int i = 0; i < tamanho; i++) {
        caminho->percurso[i] = percurso[i];
    }
}

void caminho_set_custo(CAMINHO* caminho, int custo){
    caminho->custo = custo;
}