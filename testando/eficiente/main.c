#include "../EDs/item.h"
#include "../EDs/lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*
Definir uma struct para auxiliar com as arestas
*/
typedef struct {
    int cidadeA;
    int cidadeB;
    int distancia;
} Aresta;

// Função para encontrar a distância entre duas cidades
int encontrar_distancia(Aresta arestas[], int numArestas, int cidadeA, int cidadeB) {
    for (int i = 0; i < numArestas; i++) {
        // Lembrar que, se há dois vertices, A e B, a aresta AB = BA, é a mesma aresta.
        if ((arestas[i].cidadeA == cidadeA && arestas[i].cidadeB == cidadeB) ||
            (arestas[i].cidadeA == cidadeB && arestas[i].cidadeB == cidadeA)) {
            return arestas[i].distancia;
        }
    }
    return INT_MAX; // Retorna um valor grande se não houver conexão entre as cidades
}

// Função recursiva para explorar todas as rotas (backtracking)
void explorar(Aresta arestas[], int numArestas, int numCidades, LISTA* lista, bool visitado[], int cidadeAtual, int custoAtual, int* menorCusto, LISTA* melhorRota) {
    if (lista_tamanho(lista) == numCidades - 1) {
        // Verifica se é um ciclo completo e calcula o custo de retorno à cidade de origem
        int cidadeTopo = item_get_chave(lista_get_posicao(lista, lista_tamanho(lista)-1));
        int distanciaRetorno = encontrar_distancia(arestas, numArestas, cidadeTopo, item_get_chave(lista_get_posicao(lista, 0)));
        
        if (distanciaRetorno != INT_MAX) {
            int custoTotal = custoAtual + distanciaRetorno;

            // Mesma ideia do de permutação
            if (custoTotal < *menorCusto) {
                *menorCusto = custoTotal;

                // Limpa a lista de melhores rotas
                lista_limpar(melhorRota);

                // Atualiza a melhor rota
                for (int i = 0; i < lista_tamanho(lista); i++) {
                    lista_inserir(melhorRota, lista_get_posicao(lista, i));
                }
            }
        }
        return;
    }

    // Tenta visitar todas as cidades não visitadas
    for (int i = 1; i < numCidades; i++) {
        if (!visitado[i]) {
            int distancia = encontrar_distancia(arestas, numArestas, cidadeAtual, i);
            if (distancia != INT_MAX && custoAtual + distancia < *menorCusto) {
                // Marca a cidade como visitada
                visitado[i] = true;
                ITEM* novaCidade = item_criar(i, 0);
                lista_inserir(lista, novaCidade);

                // Chama recursivamente para a próxima cidade
                explorar(arestas, numArestas, numCidades, lista, visitado, i, custoAtual + distancia, menorCusto, melhorRota);

                // Desempilha e marca como não visitada (backtrack)
                ITEM *item = lista_remover_ultimo(lista);
                item_apagar(&item);
                visitado[i] = false;
            }
        }
    }
}

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

    LISTA* lista = lista_criar();
    LISTA* melhorRota = lista_criar();
    
    // Controla quais cidades já foram visitadas
    bool* visitado = (bool*) malloc(numCidades * sizeof(bool));  
    if (visitado == NULL) {
        exit(1);
    }
    
    for (int i = 0; i < numCidades; i++) {
        visitado[i] = false;
    }
    visitado[cidadeOrigem] = true; // Marca a cidade de origem como visitada

    ITEM* cidadeInicial = item_criar(cidadeOrigem, 0);
    lista_inserir(lista, cidadeInicial); // Começa pela cidade de origem

    int menorCusto = INT_MAX;

    // Explorar rotas
    explorar(arestas, numArestas, numCidades, lista, visitado, cidadeOrigem, 0, &menorCusto, melhorRota);

    // Exibir a melhor rota e o menor custo
    printf("Melhor rota: ");
    lista_print(melhorRota);
    printf("\nCusto da melhor rota: %d\n", menorCusto);

    // Limpeza
    lista_apagar(&lista);
    lista_apagar(&melhorRota);
    free(arestas);
    free(visitado);

    return 0;
}