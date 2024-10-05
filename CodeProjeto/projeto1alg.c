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
        // Lembrar que, se há dois vertices, A e B, a aresta AB = BA, é a mesma aresta.
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
    // Adiciona o custo de retorno à cidade de origem
    ITEM *ultimaCidade = pilha_topo(pilha);
    ITEM *cidadeOrigem = pilha->item[0];

    // Profundidade da árvore gerada até o momento
    int distanciaRetorno = encontrarDistancia(arestas, numArestas, item_get_chave(ultimaCidade), item_get_chave(cidadeOrigem));
    
    if (distanciaRetorno == INT_MAX)
        return INT_MAX;
    
    custo += distanciaRetorno;
    return custo;
}

// Função para gerar todas as permutações de cidades de forma iterativa
void permutacaoIterativa(Aresta arestas[], int numArestas, PILHA *melhorRota, int *menorCusto, int numCidades) {
    PILHA *pilha = pilha_criar(); // Cria uma pilha para armazenar a rota
    bool visitado[numCidades];    // Array para controlar cidades visitadas

    // Coloca todas como não visitadas.
    for (int i = 0; i < numCidades; i++) {
        visitado[i] = false;
    }

    // Começa pela cidade de origem (cidade 0)
    ITEM *cidadeOrigem = item_criar(0, 0); // Cidade 0 com peso 0
    pilha_empilhar(pilha, cidadeOrigem);
    visitado[0] = true;

    while (!pilha_vazia(pilha)) {
        ITEM *cidadeAtual = pilha_desempilhar(pilha); // Desempilha o topo da pilha
        int idCidadeAtual = item_get_chave(cidadeAtual);
        visitado[idCidadeAtual] = false;

        if (pilha_tamanho(pilha) == numCidades - 1) {
            // Se uma rota completa é formada

            // Então calcula-se o custo total desta rota
            int custo = calcularCusto(arestas, numArestas, pilha);
            if (custo < *menorCusto) {
                *menorCusto = custo;
                // Atualiza a melhor rota

                // Depois segue a melhor rota (ramo) 
                for (int i = 0; i < pilha_tamanho(pilha); i++) {
                    ITEM *cidade = pilha->item[i];
                    pilha_empilhar(melhorRota, cidade);
                }
            }
            continue;
        }

        // Empilha as próximas cidades não visitadas

        // Expandir o caminho atual, "gerar" novas rotas, explorar as que ainda não foram 
        // exploradas
        for (int i = numCidades - 1; i >= 0; i--) {
            if (!visitado[i]) {
                visitado[i] = true;
                ITEM *novaCidade = item_criar(i, 0); // Criar item cidade
                pilha_empilhar(pilha, novaCidade);
            }
        }

    }
    pilha_apagar(&pilha); // Libera a pilha ao final
}

int main(int argc, char *argv[]) {
    // Abrir o arquivo
    FILE* arq = fopen("cidades.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numCidades, cidadeOrigem, numArestas;

    // Ler nº de Cidades e a cidade de origem
    fscanf(arq, "%d", &numCidades);
    fscanf(arq, "%d", &cidadeOrigem);
    fscanf(arq, "%d", &numArestas);

    Aresta arestas[numArestas];
    for (int i = 0; i < numArestas; i++) {
        fscanf(arq, "%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB, &arestas[i].distancia);
    }
    fclose(arq);

    // No final deve aparecer a rota, logo, podemos empilhar as de melhor escolha.
    PILHA *melhorRota = pilha_criar();
    int menorCusto = INT_MAX;

    // Chama a função de permutação para encontrar a melhor rota
    permutacaoIterativa(arestas, numArestas, melhorRota, &menorCusto, numCidades);

    printf("Melhor rota: \n");
    pilha_print(melhorRota);
    printf("\nMenor custo: %d\n", menorCusto);

    pilha_apagar(&melhorRota); // Libera a memória da pilha

    return 0;
}
