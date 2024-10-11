#include "cidade.h"
#include "pilha.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

// Função de Depth For Search
void dfs(int cidade_atual, int distancia_atual, int cidade_inicial,
         int n_cidades, CIDADE **cidades, PILHA *stack, PILHA *melhor_caminho,
         int *visitado, int *min_distancia) {

  ITEM *item_atual = item_criar(cidade_atual, NULL);
  pilha_empilhar(stack, item_atual);
  visitado[cidade_atual] = 1;

  if (pilha_tamanho(stack) == n_cidades) {
    /*
     * Condição que garante que vamos voltar à cidade inicial.
     * Se chegarmos aqui, nosso caminho é completo, mas não necessariamente
     * vai ser o melhor
     */
    ESTRADA *estrada = cidade_conexoes(cidades[cidade_atual]);
    bool caminho_fechado = false;
    while (estrada) {
      if (estrada_destino(estrada) == cidade_inicial) {
        distancia_atual += estrada_distancia(estrada);
        caminho_fechado = true;
        break;
      }
      estrada = estrada_proxima(estrada);
    }

    /* Se o caminho atual for melhor que o melhor, */
    if (caminho_fechado && distancia_atual < *min_distancia) {
      *min_distancia = distancia_atual;

      /* Atualizamos o melhor caminho */
      pilha_transferir(stack, melhor_caminho);
    }

  } else { /* Senão, começa a explorar outro caminho */
    ESTRADA *estrada = cidade_conexoes(cidades[cidade_atual]);

    while (estrada) {
      int destino = estrada_destino(estrada);
      if (!visitado[destino]) {
        dfs(destino, distancia_atual + estrada_distancia(estrada),
            cidade_inicial, n_cidades, cidades, stack, melhor_caminho, visitado,
            min_distancia);
      }

      estrada = estrada_proxima(estrada);
    }
  }

  visitado[cidade_atual] = 0;
  ITEM *it = pilha_desempilhar(stack);
  item_apagar(&it);
}

/* Função de resolução do problema usando a pilha */
void caixeiro_viajante(int n_cidades, int cidade_inicial, CIDADE **cidades) {
  PILHA *stack = pilha_criar();
  int *visitado = (int *)calloc(n_cidades, sizeof(int));
  int min_distancia = INT_MAX; /* Inicialmente, o "infinito" */
  PILHA *melhor_caminho = pilha_criar();

  /* Inicia a busca em profundidade a partir da cidade inicial
   * Sempre retorna o melhor caminho, ou, caso não seja possível,
   * não modifica a variável. */

  // Depth for Search
  dfs(cidade_inicial, 0, cidade_inicial, n_cidades, cidades, stack,
      melhor_caminho, visitado, &min_distancia);

  /* Melhor caminho achado, desempilha a rota e imprime a mesma */
  if (min_distancia < INT_MAX) {
    pilha_inverter(melhor_caminho);
    printf("Melhor caminho: ");
    while (pilha_tamanho(melhor_caminho) > 0) {
      ITEM *it = pilha_desempilhar(melhor_caminho);
      printf("%d -> ", item_get_chave(it) + 1);
      item_apagar(&it);
    }
    printf("%d\n", cidade_inicial + 1);

    printf("\nDistância mínima: %d\n", min_distancia);
  } else { /* O valor foi o "infinito" então não tem rota */
    printf("Nenhum caminho válido encontrado.\n");
  }

  pilha_apagar(&stack);
  pilha_apagar(&melhor_caminho);
  free(visitado);
}

int main() {
  int n_cidades, cidade_inicial, n_arestas;

  /* Ler informações do problema */
  scanf("%d", &n_cidades);
  scanf("%d", &cidade_inicial);
  scanf("%d", &n_arestas);

  CIDADE **cidades = (CIDADE **)malloc(n_cidades * sizeof(CIDADE *));
  for (int i = 0; i < n_cidades; i++) {
    cidades[i] = cidade_criar(i);
  } /* Lista de cidades que temos de percorrer */

  /* Conectar as cidades com estradas */
  for (int i = 0; i < n_arestas; i++) {
    /* Nossa entrada começa em 1, porém, nosso programa é 0 indexado,
     * então o ajuste é feito subtraindo - 1 */
    int cidade1, cidade2, distancia;
    scanf("%d%d%d", &cidade1, &cidade2, &distancia);
    adicionar_estrada(cidades[cidade1 - 1], cidade2 - 1, distancia);
    adicionar_estrada(cidades[cidade2 - 1], cidade1 - 1, distancia);
  }

  /* Resolve o problema */
  caixeiro_viajante(n_cidades, cidade_inicial - 1, cidades);

  /* Limpeza de memória */
  for (int i = 0; i < n_cidades; i++) {
    ESTRADA *e = cidade_conexoes(cidades[i]);
    while (e != NULL) {
      ESTRADA *prox = estrada_proxima(e);
      free(e);
      e = prox;
    }
    free(cidades[i]);
  }
  free(cidades);

  return 0;
}
