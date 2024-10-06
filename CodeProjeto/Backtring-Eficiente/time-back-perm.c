#include "../item.h"
#include "../pilha.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int cidadeA;
  int cidadeB;
  int distancia;
} Aresta;

// Protocolos das Funções
void explorarRotas(Aresta[], int, int, PILHA *, bool[], int, int, int *, PILHA *);
void permutacaoIterativa(Aresta[], int, PILHA *, int *, int);

// Função wrapper para adaptar a assinatura da função `explorarRotas`
void wrapperExplorarRotas(Aresta arestas[], int numArestas, PILHA *melhorRota, int *menorCusto, int numCidades) {
	PILHA *pilha = pilha_criar();
	bool visitado[numCidades];
	for (int i = 0; i < numCidades; i++)
		visitado[i] = false;

	int cidadeOrigem = 0;
	visitado[cidadeOrigem] = true;
	ITEM *cidadeInicial = item_criar(cidadeOrigem, 0);
	pilha_empilhar(pilha, cidadeInicial);

	explorarRotas(arestas, numArestas, numCidades, pilha, visitado, cidadeOrigem, 0, menorCusto, melhorRota);

	pilha_apagar(&pilha);
}

// Função para medir o tempo de execução de uma função
void medirTempoExecucao(void (*funcao)(Aresta[], int, PILHA *, int *, int), Aresta arestas[], int numArestas, PILHA *melhorRota, int *menorCusto, int numCidades) {
	clock_t inicio, fim;
	double tempoGasto;

	inicio = clock();

	// Executa a função passada como parâmetro
	funcao(arestas, numArestas, melhorRota, menorCusto, numCidades);

	fim = clock(); // Captura o tempo de fim
	tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC; 
	// Calcula o tempo gasto em segundos
	// Cria-se um período dividindo pelo clocks_per_sec.
	printf("Tempo de execução: %f segundos\n", tempoGasto);
}

// Função para encontrar a distância entre duas cidades
int encontrarDistancia(Aresta arestas[], int numArestas, int cidadeA, int cidadeB) {
	for (int i = 0; i < numArestas; i++) {
		// Arestas A->B, do vértice A para B, é a mesma do B->A
		if ((arestas[i].cidadeA == cidadeA && arestas[i].cidadeB == cidadeB) ||
			(arestas[i].cidadeA == cidadeB && arestas[i].cidadeB == cidadeA)) {
			return arestas[i].distancia;
		}
	}
	// Se não for encontrado a distância, retorna um valor muito grande
	return INT_MAX;
}

// Função para calcular o custo de uma rota completa
int calcularCusto(Aresta arestas[], int numArestas, PILHA *pilha) {
	int custo = 0;

	// Calcular distâncias consecutivas
	for (int i = 0; i < pilha_tamanho(pilha) - 1; i++) {
		ITEM *cidadeAtual = pilha->item[i];
		ITEM *cidadeProxima = pilha->item[i + 1];
		int distancia =
			encontrarDistancia(arestas, numArestas, item_get_chave(cidadeAtual),
							item_get_chave(cidadeProxima));
		if (distancia == INT_MAX)
			return INT_MAX;

		custo += distancia;
	}
	ITEM *ultimaCidade = pilha_topo(pilha);
	ITEM *cidadeOrigem = pilha->item[0];

  	int distanciaRetorno = encontrarDistancia(arestas, numArestas, item_get_chave(ultimaCidade), item_get_chave(cidadeOrigem));

	if (distanciaRetorno == INT_MAX)
		return INT_MAX;

	// se não houver um caminho direto entre a última cidade e a cidade de origem, 
	// (distanciaRetorno == INT_MAX), a função retorna INT_MAX, invalidando a rota.
	// E se a distância for válida, ela é adicionada ao custo total.

	custo += distanciaRetorno;
	return custo;
}

// Função recursiva para explorar rotas (backtracking)
void explorarRotas(Aresta arestas[], int numArestas, int numCidades, PILHA *pilha, bool visitado[], int cidadeAtual, int custoAtual, int *menorCusto, PILHA *melhorRota) {

	// verifica se a rota está completa, não contando com a de origem
	if (pilha_tamanho(pilha) == numCidades - 1) {
		int cidadeTopo = item_get_chave(pilha_topo(pilha));
		int distanciaRetorno = encontrarDistancia(arestas, numArestas, cidadeTopo, item_get_chave(pilha->item[0]));

		// ciclo completo, no caso, da última até a primeira cidade.
		if (distanciaRetorno != INT_MAX) {
			int custoTotal = custoAtual + distanciaRetorno;
			if (custoTotal < *menorCusto) {
				*menorCusto = custoTotal;
				for (int i = 0; i < pilha_tamanho(pilha); i++) {
					pilha_empilhar(melhorRota, pilha->item[i]);
				}
			}
		}

		return;
  	}

    // Explorar outras rotas, tirando a de origem
	for (int i = 1; i <= numCidades; i++) {
		if (!visitado[i]) {
			int distancia = encontrarDistancia(arestas, numArestas, cidadeAtual, i);
			// caso Rota inválida E caso da distância encontrada agora for a menor para atualizar
			if (distancia != INT_MAX && custoAtual + distancia < *menorCusto) {
				visitado[i] = true;
				ITEM *novaCidade = item_criar(i, 0);
				pilha_empilhar(pilha, novaCidade);
				explorarRotas(arestas, numArestas, numCidades, pilha, visitado, i, custoAtual + distancia, menorCusto, melhorRota);
				// chama recursivamente, só que agora com a atual sendo i,
				// e o custoAtual + 
				ITEM *item = pilha_desempilhar(pilha);
				item_apagar(&item);
				visitado[i] = false;
			}
		}
	}
}

// Função para gerar permutações iterativas de cidades
void permutacaoIterativa(Aresta arestas[], int numArestas, PILHA *melhorRota, int *menorCusto, int numCidades) {
	PILHA *pilha = pilha_criar();
	bool visitado[numCidades];
	for (int i = 0; i < numCidades; i++) {
		visitado[i] = false;
	}
	ITEM *cidadeOrigem = item_criar(0, 0);
	pilha_empilhar(pilha, cidadeOrigem);
	visitado[0] = true;

	while (!pilha_vazia(pilha)) {
		ITEM *cidadeAtual = pilha_desempilhar(pilha);
		int idCidadeAtual = item_get_chave(cidadeAtual);
		visitado[idCidadeAtual] = false;

		if (pilha_tamanho(pilha) == numCidades - 1) {
			int custo = calcularCusto(arestas, numArestas, pilha);
			if (custo < *menorCusto) {
				*menorCusto = custo;
				for (int i = 0; i < pilha_tamanho(pilha); i++) {
					ITEM *cidade = pilha->item[i];
					pilha_empilhar(melhorRota, cidade);
				}
			}
			continue;
		}

		for (int i = numCidades - 1; i >= 0; i--) {
			if (!visitado[i]) {
				visitado[i] = true;
				ITEM *novaCidade = item_criar(i, 0);
				pilha_empilhar(pilha, novaCidade);
			}
		}
	}
	pilha_apagar(&pilha);
}

int main() {
	FILE *arquivo = fopen("cidades.txt", "r");
	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return -1;
	}

	int numCidades, cidadeOrigem, numArestas;

	fscanf(arquivo, "%d", &numCidades);
	fscanf(arquivo, "%d", &cidadeOrigem);
	fscanf(arquivo, "%d", &numArestas);

	Aresta arestas[numArestas];
	for (int i = 0; i < numArestas; i++) {
		fscanf(arquivo, "%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB, &arestas[i].distancia);
	}

	// Após a leitura de todo arquivo, podemos fechá-lo
	fclose(arquivo);

	// Inicializa a pilha para armazenar a melhor rota
	PILHA *melhorRota = pilha_criar();
	int menorCusto = INT_MAX;

	// Medir tempo de execução do backtracking
	printf("Backtracking:\n");
	medirTempoExecucao(wrapperExplorarRotas, arestas, numArestas, melhorRota, &menorCusto, numCidades);

	// Medir tempo de execução da permutação iterativa
	printf("Permutação iterativa:\n");
	medirTempoExecucao(permutacaoIterativa, arestas, numArestas, melhorRota, &menorCusto, numCidades);

	// Exibir a melhor rota e o menor custo
	printf("Melhor rota: ");
	pilha_print(melhorRota);
	printf("\nCusto da melhor rota: %d\n", menorCusto);

	pilha_apagar(&melhorRota);

	return 0;
}