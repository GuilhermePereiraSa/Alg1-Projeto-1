#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "lista.h"
#include "item.h"

#define MAX_CIDADES 100  // Número máximo de cidades

// Estrutura para armazenar as arestas
typedef struct {
    int cidadeA;
    int cidadeB;
    int distancia;
} Aresta;

// Matriz de distâncias entre cidades
int distancias[MAX_CIDADES][MAX_CIDADES];
char nomes_cidades[MAX_CIDADES][50];
int num_cidades = 0;

// Função para ler os dados do arquivo
LISTA *ler_arquivo(const char *nome_arquivo) {
    FILE *file = fopen(nome_arquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    int numCidades, cidadeOrigem, numArestas;
    fscanf(file, "%d", &numCidades);  // Lê o número de cidades
    fscanf(file, "%d", &cidadeOrigem); // Lê a cidade de origem
    fscanf(file, "%d", &numArestas);  // Lê o número de arestas

    // Verifica se o número de cidades é válido
    if (numCidades > MAX_CIDADES) {
        printf("Número de cidades excede o limite máximo de %d.\n", MAX_CIDADES);
        fclose(file);
        return NULL;
    }

    // Lê as arestas e distâncias
    Aresta arestas[numArestas];
    for (int i = 0; i < numArestas; i++) {
        fscanf(file, "%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB, &arestas[i].distancia);

        // Armazena as distâncias na matriz
        distancias[arestas[i].cidadeA][arestas[i].cidadeB] = arestas[i].distancia;
        distancias[arestas[i].cidadeB][arestas[i].cidadeA] = arestas[i].distancia; // Distância simétrica
    }

    // Inicializa a lista de cidades
    LISTA *lista_cidades = lista_criar(ORDENADA);

    // Preenche as cidades na lista
    for (int i = 0; i < numCidades; i++) {
        // Criar um item com o nome da cidade
        ITEM *item = item_criar(i, (void *)nomes_cidades[i]);
        lista_inserir(lista_cidades, item);
    }

    fclose(file);
    return lista_cidades;
}

// Função para calcular a distância total de uma rota
int calcular_distancia_total(int *rota, int n) {
    int distancia_total = 0;
    for (int i = 0; i < n - 1; i++) {
        distancia_total += distancias[rota[i]][rota[i + 1]];
    }
    distancia_total += distancias[rota[n - 1]][rota[0]]; // Retorno à cidade inicial
    return distancia_total;
}

// Função para o Algoritmo de Vizinho Mais Próximo
void caixeiro_viajante_vizinho_mais_proximo(int *rota, int n) {
    int visitado[n];
    for (int i = 0; i < n; i++) {
        visitado[i] = 0;
    }

    int cidade_atual = 0;  // Começa pela primeira cidade
    visitado[cidade_atual] = 1;
    rota[0] = cidade_atual;

    for (int i = 1; i < n; i++) {
        int cidade_proxima = -1;
        int menor_distancia = INT_MAX;

        // Encontra a cidade mais próxima
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && distancias[cidade_atual][j] < menor_distancia) {
                menor_distancia = distancias[cidade_atual][j];
                cidade_proxima = j;
            }
        }

        rota[i] = cidade_proxima;
        visitado[cidade_proxima] = 1;
        cidade_atual = cidade_proxima;
    }
}

// Função para a função principal
int main() {
    const char *nome_arquivo = "cidades.txt";

    // Lê os dados do arquivo
    LISTA *lista_cidades = ler_arquivo(nome_arquivo);
    if (lista_cidades == NULL) {
        return -1;
    }

    int n = lista_tamanho(lista_cidades);
    if (n == 0) {
        printf("Lista de cidades vazia.\n");
        return -1;
    }

    int rota[n];

    // Preenche a rota com os IDs das cidades
    ITEM *item;
    for (int i = 0; i < n; i++) {
        item = lista_buscar(lista_cidades, i);
        if (item) {
            rota[i] = item_get_chave(item);
        }
    }

    // Aplica o algoritmo do Vizinho Mais Próximo
    caixeiro_viajante_vizinho_mais_proximo(rota, n);

    // Exibe o melhor caminho encontrado
    printf("Melhor Rota (Aproximação de Vizinho Mais Próximo): ");
    for (int i = 0; i < n; i++) {
        printf("%s ", nomes_cidades[rota[i]]);
    }
    printf("\n");

    // Calcula e exibe o custo total
    int custo_total = calcular_distancia_total(rota, n);
    printf("Custo Total: %d\n", custo_total);

    // Limpeza
    lista_apagar(&lista_cidades);

    return 0;
}
