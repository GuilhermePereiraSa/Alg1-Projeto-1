#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "lista.h"
#include "aresta.h"
#include "caminho.h"

#define ORDENADA true

/**
 * Essa função cria um vetor para armazenar as cidades do percurso, que serão permutadas posteriormente
 */
int* cria_vetor(int numCidade){
    int* vetor = (int*) malloc(sizeof(int) * numCidade);
    for(int i = 1; i <= numCidade; i++){
        vetor[i-1] = i;
    }
    return vetor;
}

/**
 * Função usada para realizar a permutação das cidades, responsável por fazer as trocas
 */
void troca(int vetor[], int i, int j){
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

/**
 * Essa função calcula o custo total de um percurso utilizando a matriz de distâncias
 */
int calcula_custo_percurso(int vetor[], int matriz[][12], int numCidades) {
    int custo = 0;
    for(int i = 0; i < numCidades - 1; i++) {
        custo += matriz[vetor[i] - 1][vetor[i + 1] - 1];
    }
    custo += matriz[vetor[numCidades - 1] - 1][vetor[0] - 1]; // Retorno para cidade de origem
    return custo;
}

/**
 * Função recursiva responsável por gerar as permutações e calcular o menor caminho
 */
void gera_caminhos(int vetor[], int ini, int fim, int matriz[][12], int numCidades, CAMINHO* caminho_menor_custo){
    if(ini == fim){ 
        int custo_atual_caminho = calcula_custo_percurso(vetor, matriz, numCidades);
        if(custo_atual_caminho < caminho_get_custo(caminho_menor_custo)){
            caminho_set_custo(caminho_menor_custo, custo_atual_caminho);
            caminho_set_percurso(caminho_menor_custo, vetor, numCidades);
        }
    } else {
        for(int i = ini; i <= fim; i++){
            troca(vetor, ini, i);
            gera_caminhos(vetor, ini + 1, fim, matriz, numCidades, caminho_menor_custo);
            troca(vetor, ini, i); // Backtrack
        }
    }
}

/**
 * Essa função cria a matriz de distâncias entre as cidades
 */
void cria_matriz_distancias(LISTA* lista_input, int matriz[][12], int numArestas){
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 12; j++) {
            matriz[i][j] = (i == j) ? 0 : INT_MAX; // Custo 0 para a mesma cidade, infinito para as outras
        }
    }

    ARESTA* tmp_aresta;
    for(int i = 1; i <= numArestas; i++){
        tmp_aresta = lista_busca(lista_input, i);
        int cidadeA = aresta_cidade_a(tmp_aresta) - 1;
        int cidadeB = aresta_cidade_b(tmp_aresta) - 1;
        int distancia = aresta_distancia(tmp_aresta);
        matriz[cidadeA][cidadeB] = distancia;
        matriz[cidadeB][cidadeA] = distancia;
    }
}

/**
 * Função principal que realiza a leitura dos dados do arquivo, cria lista de arestas, inicializa o caminho de menor custo e imprime o resultado
 */
int main(void){
    int numCidades, cidadeOrigem, numArestas;
    scanf("%d %d %d", &numCidades, &cidadeOrigem, &numArestas);

    int* vet_caminho_menor_custo = (int*) calloc(numCidades, sizeof(int));

    CAMINHO* caminho_menor_custo = caminho_inicializa(INT_MAX, vet_caminho_menor_custo, numCidades);

    LISTA* lista_input = lista_criar(ORDENADA);
    int tmp_cidade_A, tmp_cidade_B, tmp_distancia;
    for(int i = 1; i <= numArestas; i++){
        scanf("%d %d %d", &tmp_cidade_A, &tmp_cidade_B, &tmp_distancia);
        lista_inserir(lista_input, aresta_criar(tmp_cidade_A, tmp_cidade_B, tmp_distancia, i));
    }

    // Cria matriz de distâncias
    int matriz[12][12];
    cria_matriz_distancias(lista_input, matriz, numArestas);

    // Gera os caminhos
    int* vet_cidades = cria_vetor(numCidades);
    gera_caminhos(vet_cidades, 0, numCidades - 1, matriz, numCidades, caminho_menor_custo);

    vet_caminho_menor_custo = caminho_get_percurso(caminho_menor_custo);

    printf("O custo do menor caminho é: %d\n", caminho_get_custo(caminho_menor_custo));
    printf("O percurso é: ");
    for(int i = 0; i < numCidades; i++){
        printf("%d-", vet_caminho_menor_custo[i]);
    }
    printf("%d\n", vet_caminho_menor_custo[0]);

    free(vet_cidades);
    return 0;
}
