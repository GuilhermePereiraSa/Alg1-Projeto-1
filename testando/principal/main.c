#include "../EDs/item.h"
#include "../EDs/lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/*
Função principal que coordena o programa.
*/
int main(void) {
    int numCidades, cidadeOrigem, numArestas;
    scanf("%d %d %d", &numCidades, &cidadeOrigem, &numArestas);

    Aresta* arestas = (Aresta*) malloc(numArestas * sizeof(Aresta));
    if (arestas == NULL) {
        exit(1);
    }

    //Ler arestas 
    for (int i = 0; i < numArestas; i++) {
        scanf("%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB, &arestas[i].distancia);
    }

    

    return 0;
}