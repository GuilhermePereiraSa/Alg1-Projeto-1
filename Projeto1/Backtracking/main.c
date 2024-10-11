#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <time.h>

#include "lista.h"
#include "aresta.h"

/**
 * Essa função cria um vetor para armazenar as cidades do percurso, com a cidade de origem fixada no início
 */
int* cria_vetor(int numCidade, int cidadeOrigem) {
    int* vetor = (int*) malloc(sizeof(int) * numCidade);
    vetor[0] = cidadeOrigem; // A cidade de origem é colocada na primeira posição
    int index = 1;
    for (int i = 1; i <= numCidade; i++) {
        if (i != cidadeOrigem) {
            vetor[index++] = i;
        }
    }
    return vetor;
}

/**
 * Função usada para realizar a permutação das cidades, responsável por fazer as trocas
 */
void troca(int vetor[], int i, int j) {
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

/**
 * Função recursiva responsável por gerar as permutações e calcular o menor caminho
 * utilizando a técnica de backtracking
 */
void backtracking(int vetor[], int ini, int matriz[][12], int numCidades, int custo_parcial, int* melhor_custo, int* melhor_percurso) {
    if (ini == numCidades) {
        // Fechando o ciclo, adicionando o custo de volta à cidade de origem
        if (matriz[vetor[numCidades - 1] - 1][vetor[0] - 1] != INT_MAX) {
            custo_parcial += matriz[vetor[numCidades - 1] - 1][vetor[0] - 1];
            if (custo_parcial < *melhor_custo) {
                *melhor_custo = custo_parcial;
                for (int i = 0; i < numCidades; i++) {
                    melhor_percurso[i] = vetor[i];
                }
            }
        }
    } else {
        for (int i = ini; i < numCidades; i++) {
            troca(vetor, ini, i);
            int nova_custo_parcial = custo_parcial;

            if (ini > 0) {
                int custo_aresta = matriz[vetor[ini - 1] - 1][vetor[ini] - 1];
                if (custo_aresta == INT_MAX) {
                    troca(vetor, ini, i); // Desfazer a troca (backtrack)
                    continue; // Ignorar caminhos inválidos
                }
                nova_custo_parcial += custo_aresta;
            }

            // Condição de poda
            if (nova_custo_parcial < *melhor_custo) {
                backtracking(vetor, ini + 1, matriz, numCidades, nova_custo_parcial, melhor_custo, melhor_percurso);
            }

            troca(vetor, ini, i); // Desfazer a troca (backtrack)
        }
    }
}

/**
 * Função para criar a matriz de distâncias entre as cidades
 */
void cria_matriz_distancias(LISTA* lista_input, int matriz[][12], int numArestas) {
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            matriz[i][j] = (i == j) ? 0 : INT_MAX; // Custo 0 para a mesma cidade, infinito para as outras
        }
    }

    ARESTA* tmp_aresta;
    for (int i = 1; i <= numArestas; i++) {
        tmp_aresta = lista_busca(lista_input, i);
        int cidadeA = aresta_cidade_a(tmp_aresta) - 1;
        int cidadeB = aresta_cidade_b(tmp_aresta) - 1;
        int distancia = aresta_distancia(tmp_aresta);
        matriz[cidadeA][cidadeB] = distancia;
        matriz[cidadeB][cidadeA] = distancia;
    }
}

/**
 * Função para medir o tempo de execução do backtracking
 */
double medir_tempo_backtracking(int* vetor, int matriz[][12], int numCidades, int* melhor_custo, int* melhor_percurso) {
    clock_t inicio, fim;
    double tempo_gasto;

    // Início da contagem de tempo
    inicio = clock();

    // Executa o backtracking
    backtracking(vetor, 1, matriz, numCidades, 0, melhor_custo, melhor_percurso);

    // Fim da contagem de tempo
    fim = clock();

    // Calcula o tempo gasto
    tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    return tempo_gasto;
}

int main(void) {
    int numCidades, cidadeOrigem, numArestas;
    scanf("%d %d %d", &numCidades, &cidadeOrigem, &numArestas);

    int* vet_caminho_menor_custo = (int*) calloc(numCidades, sizeof(int));
    int melhor_custo = INT_MAX;

    LISTA* lista_input = lista_criar(true);
    int tmp_cidade_A, tmp_cidade_B, tmp_distancia;
    for (int i = 1; i <= numArestas; i++) {
        scanf("%d %d %d", &tmp_cidade_A, &tmp_cidade_B, &tmp_distancia);
        lista_inserir(lista_input, aresta_criar(tmp_cidade_A, tmp_cidade_B, tmp_distancia, i));
    }

    // Cria matriz de distâncias
    int matriz[12][12];
    cria_matriz_distancias(lista_input, matriz, numArestas);

    // Gera os caminhos
    int* vet_cidades = cria_vetor(numCidades, cidadeOrigem); // Passa a cidade de origem

    // Mede o tempo do backtracking
    double tempo_gasto = medir_tempo_backtracking(vet_cidades, matriz, numCidades, &melhor_custo, vet_caminho_menor_custo);

    // Imprime os resultados
    printf("O custo do menor caminho é: %d\n", melhor_custo);
    printf("O percurso é: ");
    for (int i = 0; i < numCidades; i++) {
        printf("%d-", vet_caminho_menor_custo[i]);
    }
    printf("%d\n", vet_caminho_menor_custo[0]);

    printf("Tempo gasto pelo backtracking: %.6f segundos\n", tempo_gasto);

    // Libera memória alocada
    free(vet_cidades);
    free(vet_caminho_menor_custo);
    return 0;
}