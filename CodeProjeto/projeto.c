#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "pilha.h"
#include "item.h"

typedef struct {
    int cidadeA;
    int cidadeB;
    int distancia;
} Aresta;

// Função para encontrar a distância entre duas cidades
int encontrarDistancia(Aresta arestas[], int numArestas, int cidadeA, int cidadeB) {
    for (int i = 0; i < numArestas; i++) {
        if ((arestas[i].cidadeA == cidadeA && arestas[i].cidadeB == cidadeB) ||
            (arestas[i].cidadeA == cidadeB && arestas[i].cidadeB == cidadeA)) {
            return arestas[i].distancia;
        }
    }
    return INT_MAX; // Retorna um valor grande se não houver conexão entre as cidades
}

// Função para calcular o custo de uma rota completa
int calcularCusto(Aresta arestas[], int numArestas, PILHA *pilha) {
    int custo = 0;

    for (int i = 0; i < pilha_tamanho(pilha) - 1; i++) {
        ITEM *cidadeAtual = pilha->item[i];
        ITEM *cidadeProxima = pilha->item[i + 1];
        int distancia = encontrarDistancia(arestas, numArestas, item_get_chave(cidadeAtual), item_get_chave(cidadeProxima));
        if (distancia == INT_MAX)
            return INT_MAX; // Se não houver conexão, rota inválida
        custo += distancia;
    }

    ITEM *ultimaCidade = pilha_topo(pilha);
    ITEM *cidadeOrigem = pilha->item[0];
    int distanciaRetorno = encontrarDistancia(arestas, numArestas, item_get_chave(ultimaCidade), item_get_chave(cidadeOrigem));

    if (distanciaRetorno == INT_MAX)
        return INT_MAX;

    custo += distanciaRetorno;
    return custo;
}

// Função de permutação otimizada por força bruta
void permutacaoIterativa(Aresta arestas[], int numArestas, PILHA *melhorRota, int *menorCusto, int numCidades) {
    PILHA *pilha = pilha_criar();
    bool visitado[numCidades];  // Array para controlar cidades visitadas

    for (int i = 0; i < numCidades; i++) {
        visitado[i] = false;
    }

    // Começar com a cidade de origem
    ITEM *cidadeOrigem = item_criar(0, 0);
    pilha_empilhar(pilha, cidadeOrigem);
    visitado[0] = true;

    while (!pilha_vazia(pilha)) {
        // Desempilha a cidade atual
        ITEM *cidadeAtual = pilha_desempilhar(pilha);
        int idCidadeAtual = item_get_chave(cidadeAtual);
        visitado[idCidadeAtual] = false;

        // Verifica se todas as cidades já foram visitadas
        if (pilha_tamanho(pilha) == numCidades - 1) {
            int custo = calcularCusto(arestas, numArestas, pilha);
            if (custo < *menorCusto) {
                *menorCusto = custo;
                pilha_limpar(melhorRota);
                for (int i = 0; i < pilha_tamanho(pilha); i++) {
                    ITEM *cidade = pilha->item[i];
                    pilha_empilhar(melhorRota, cidade);
                }
            }
        }

        // Tentar empilhar as cidades não visitadas
        for (int i = numCidades - 1; i >= 0; i--) {
            if (!visitado[i]) {
                visitado[i] = true;
                ITEM *novaCidade = item_criar(i, 0);
                pilha_empilhar(pilha, novaCidade);
            }
        }

        item_apagar(&cidadeAtual); // Apaga a cidade atual que foi desempilhada
    }

    pilha_apagar(&pilha); // Libera a pilha no final
}

int main(int argc, char *argv[]) {
    FILE* arq = fopen("cidades.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numCidades, cidadeOrigem, numArestas;

    fscanf(arq, "%d", &numCidades);
    fscanf(arq, "%d", &cidadeOrigem);
    fscanf(arq, "%d", &numArestas);

    Aresta arestas[numArestas];
    for (int i = 0; i < numArestas; i++) {
        fscanf(arq, "%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB, &arestas[i].distancia);
    }
    fclose(arq);

    PILHA *melhorRota = pilha_criar();
    int menorCusto = INT_MAX;

    permutacaoIterativa(arestas, numArestas, melhorRota, &menorCusto, numCidades);

    printf("Melhor rota: \n");
    pilha_print(melhorRota);
    printf("\nMenor custo: %d\n", menorCusto);

    pilha_apagar(&melhorRota);

    return 0;
}
