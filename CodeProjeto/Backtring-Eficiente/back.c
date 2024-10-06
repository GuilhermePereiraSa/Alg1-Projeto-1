#include <limits.h> // Para usar o valor INT_MAX
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../pilha.h"
#include "../item.h"

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

// Função recursiva para explorar todas as rotas (backtracking)
void explorarRotas(Aresta arestas[], int numArestas, int numCidades, PILHA* pilha, bool visitado[], int cidadeAtual, int custoAtual, int* menorCusto, PILHA* melhorRota) {
    if (pilha_tamanho(pilha) == numCidades - 1) {
        // Verifica se é um ciclo completo e calcula o custo de retorno à cidade de origem
        int cidadeTopo = item_get_chave(pilha_topo(pilha));
        int distanciaRetorno = encontrarDistancia(arestas, numArestas, cidadeTopo, item_get_chave(pilha->item[0]));
        
        if (distanciaRetorno != INT_MAX) {
            int custoTotal = custoAtual + distanciaRetorno;

            // Mesma ideia do de permutação
            if (custoTotal < *menorCusto) {
                *menorCusto = custoTotal;

                // Atualiza a melhor rota
                for (int i = 0; i < pilha_tamanho(pilha); i++) {
                    pilha_empilhar(melhorRota, pilha->item[i]);
                }
            }
        }
        return;
    }

    // Tenta visitar todas as cidades não visitadas
    for (int i = 1; i <= numCidades; i++) {
        if (!visitado[i]) {
            int distancia = encontrarDistancia(arestas, numArestas, cidadeAtual, i);
            if (distancia != INT_MAX && custoAtual + distancia < *menorCusto) {
                // Marca a cidade como visitada
                visitado[i] = true;
                ITEM* novaCidade = item_criar(i, 0);
                pilha_empilhar(pilha, novaCidade);

                // Chama recursivamente para a próxima cidade
                explorarRotas(arestas, numArestas, numCidades, pilha, visitado, i, custoAtual + distancia, menorCusto, melhorRota);

                // Desempilha e marca como não visitada (backtrack)
                ITEM *item = pilha_desempilhar(pilha);
                item_apagar(&item);
                visitado[i] = false;

            }
        }
    }
}

int main() {
    // Abrir o arquivo
    FILE* arquivo = fopen("cidades.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    int numCidades, cidadeOrigem, numArestas;

    // Ler o número de cidades e a cidade de origem
    fscanf(arquivo, "%d", &numCidades);
    fscanf(arquivo, "%d", &cidadeOrigem);

    // Ler o número de arestas
    fscanf(arquivo, "%d", &numArestas);

    // Armazenar as arestas
    Aresta arestas[numArestas];
    for (int i = 0; i < numArestas; i++) {
        fscanf(arquivo, "%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB, &arestas[i].distancia);
    }

    fclose(arquivo);

    // Inicializa a pilha e variáveis auxiliares
    PILHA* pilha = pilha_criar();
    PILHA* melhorRota = pilha_criar();

    bool visitado[numCidades];  // Controla quais cidades já foram visitadas
    for (int i = 0; i < numCidades; i++) {
        visitado[i] = false;
    }
    visitado[cidadeOrigem] = true; // Marca a cidade de origem como visitada

    ITEM* cidadeInicial = item_criar(cidadeOrigem, 0);
    pilha_empilhar(pilha, cidadeInicial); // Começa pela cidade de origem

    int menorCusto = INT_MAX;

    // Explorar rotas
    explorarRotas(arestas, numArestas, numCidades, pilha, visitado, cidadeOrigem, 0, &menorCusto, melhorRota);

    // Exibir a melhor rota e o menor custo
    printf("Melhor rota: ");
    pilha_print(melhorRota);
    printf("\nCusto da melhor rota: %d\n", menorCusto);

    // Limpeza
    pilha_apagar(&pilha);
    pilha_apagar(&melhorRota);

    return 0;
}
