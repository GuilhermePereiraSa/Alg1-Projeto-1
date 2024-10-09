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

// Vetor de distâncias entre cidades (em vez de usar uma matriz)
Aresta distancias[MAX_CIDADES * (MAX_CIDADES - 1) / 2]; // Máximo de arestas possíveis
char nomes_cidades[MAX_CIDADES][50];
int num_cidades = 0;

// Função para encontrar a distância entre duas cidades a partir do vetor de arestas
int encontrar_distancia(int cidadeA, int cidadeB) {
    for (int i = 0; i < num_cidades * (num_cidades - 1) / 2; i++) {
        if ((distancias[i].cidadeA == cidadeA && distancias[i].cidadeB == cidadeB) || 
            (distancias[i].cidadeA == cidadeB && distancias[i].cidadeB == cidadeA)) {
            return distancias[i].distancia;
        }
    }
    return INT_MAX; // Se não encontrar, retorna um valor grande (infinito)
}

// Função para calcular a distância total de uma rota
int calcular_distancia_total(int *rota, int n) {
    int distancia_total = 0;
    for (int i = 0; i < n - 1; i++) {
        distancia_total += encontrar_distancia(rota[i], rota[i + 1]);
    }
    distancia_total += encontrar_distancia(rota[n - 1], rota[0]); // Retorno à cidade inicial
    return distancia_total;
}

// Função para gerar todas as permutações das cidades e calcular o menor custo
void caixeiro_viajante_forca_bruta(int *rota, int l, int n, int *melhor_rota, int *menor_custo) {
    if (l == n) {
        int custo = calcular_distancia_total(rota, n);
        if (custo < *menor_custo) {
            *menor_custo = custo;
            memcpy(melhor_rota, rota, n * sizeof(int)); // Copia a melhor rota encontrada
        }
    } else {
        for (int i = l; i < n; i++) {
            // Troca as cidades de posição
            int temp = rota[l];
            rota[l] = rota[i];
            rota[i] = temp;

            // Gera a próxima permutação
            caixeiro_viajante_forca_bruta(rota, l + 1, n, melhor_rota, menor_custo);

            // Desfaz a troca (backtracking)
            temp = rota[l];
            rota[l] = rota[i];
            rota[i] = temp;
        }
    }
}

// Função principal
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

    int rota[n], melhor_rota[n];
    int menor_custo = INT_MAX;

    // Preenche a rota com os IDs das cidades
    ITEM *item;
    for (int i = 0; i < n; i++) {
        item = lista_buscar(lista_cidades, i);
        if (item) {
            rota[i] = item_get_chave(item);
        }
    }

    // Aplica o algoritmo de força bruta para encontrar a melhor rota
    caixeiro_viajante_forca_bruta(rota, 0, n, melhor_rota, &menor_custo);

    // Exibe o melhor caminho encontrado
    printf("Melhor Rota (Força Bruta): ");
    for (int i = 0; i < n; i++) {
        printf("%s -> ", nomes_cidades[melhor_rota[i]]);
    }
    // Exibe o retorno à cidade inicial
    printf("%s\n", nomes_cidades[melhor_rota[0]]);

    // Exibe o custo total
    printf("Custo Total: %d\n", menor_custo);

    // Limpeza
    lista_apagar(&lista_cidades);

    return 0;
}
