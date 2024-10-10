#include "item.h"
#include "lista.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

#define MAX_CIDADES 100

// Estrutura para armazenar as arestas
typedef struct {
    int cidadeA;
    int cidadeB;
    int distancia;
} Aresta;

// Função para encontrar a distância entre duas cidades a partir do vetor de arestas
int encontrar_distancia(int cidadeA, int cidadeB, Aresta *distancias, int num_arestas) {
    for (int i = 0; i < num_arestas; i++) {
        if ((distancias[i].cidadeA == cidadeA && distancias[i].cidadeB == cidadeB) ||
            (distancias[i].cidadeA == cidadeB && distancias[i].cidadeB == cidadeA)) {
            return distancias[i].distancia;
        }
    }
    return INT_MAX;  // Se não encontrar, retorna um valor grande (infinito)
}

// Função para calcular a distância total de uma rota
int calcular_distancia_total(int *rota, int n, Aresta *distancias, int num_arestas) {
    int distancia_total = 0;
    for (int i = 0; i < n - 1; i++) {
        distancia_total += encontrar_distancia(rota[i], rota[i + 1], distancias, num_arestas);
    }
    distancia_total += encontrar_distancia(rota[n - 1], rota[0], distancias, num_arestas);  // Retorno à cidade inicial
    return distancia_total;
}

// Função para gerar todas as permutações das cidades e calcular o menor custo
void caixeiro_viajante_forca_bruta(int *rota, int l, int n, int *melhor_rota, int *menor_custo, Aresta *distancias, int num_arestas) {
    if (l == n) {
        int custo = calcular_distancia_total(rota, n, distancias, num_arestas);
        if (custo < *menor_custo) {
            *menor_custo = custo;
            memcpy(melhor_rota, rota, n * sizeof(int));  // Copia a melhor rota encontrada
        }
    } else {
        for (int i = l; i < n; i++) {
            // Troca as cidades de posição
            int temp = rota[l];
            rota[l] = rota[i];
            rota[i] = temp;

            // Gera a próxima permutação
            caixeiro_viajante_forca_bruta(rota, l + 1, n, melhor_rota, menor_custo, distancias, num_arestas);

            // Desfaz a troca
            temp = rota[l];
            rota[l] = rota[i];
            rota[i] = temp;
        }
    }
}

// Função principal
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <nome_arquivo>\n", argv[0]);
        return -1;
    }

    // Nome do arquivo passado como argumento
    FILE *arquivo = fopen(argv[1], "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }

    // Cria a lista de cidades
    LISTA *lista_cidades = lista_criar();
    if (lista_cidades == NULL) {
        printf("Erro ao criar a lista de cidades.\n");
        return -1;
    }

    // Lê o número de cidades
    int num_cidades;
    fscanf(arquivo, "%d", &num_cidades);

    // Lê os nomes das cidades e insere na lista
    char nomes_cidades[MAX_CIDADES][50];
    for (int i = 0; i < num_cidades; i++) {
        fscanf(arquivo, "%s", nomes_cidades[i]);
        ITEM *item = item_criar(i, nomes_cidades[i]);
        lista_inserir(lista_cidades, item);
    }

    // Lê o número de arestas
    int num_arestas;
    fscanf(arquivo, "%d", &num_arestas);

    // Armazena as arestas (distâncias entre cidades)
    Aresta distancias[num_arestas];
    for (int i = 0; i < num_arestas; i++) {
        int cidadeA, cidadeB, distancia;
        fscanf(arquivo, "%d %d %d", &cidadeA, &cidadeB, &distancia);
        distancias[i].cidadeA = cidadeA;
        distancias[i].cidadeB = cidadeB;
        distancias[i].distancia = distancia;
    }

    fclose(arquivo);

    int rota[num_cidades], melhor_rota[num_cidades];
    int menor_custo = INT_MAX;

    // Preenche a rota com os IDs das cidades
    ITEM *item;
    for (int i = 0; i < num_cidades; i++) {
        item = lista_buscar(lista_cidades, i);
        if (item) {
            rota[i] = item_get_chave(item);
        }
    }

    // Aplica o algoritmo de força bruta para encontrar a melhor rota
    caixeiro_viajante_forca_bruta(rota, 0, num_cidades, melhor_rota, &menor_custo, distancias, num_arestas);

    // Exibe o melhor caminho encontrado
    printf("Melhor Rota (Força Bruta): ");
    for (int i = 0; i < num_cidades; i++) {
        printf("%s -> ", nomes_cidades[melhor_rota[i]]);
    }

    // Exibe o retorno à cidade inicial
    printf("%s\n", nomes_cidades[melhor_rota[0]]);

    // Exibe o custo total
    printf("Menor custo: %d\n", menor_custo);

    lista_apagar(&lista_cidades);

    return 0;
}
