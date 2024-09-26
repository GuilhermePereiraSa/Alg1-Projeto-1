/*
	No Problema do Caixeiro Viajante precisamos optar pela escolha
	mais eficiente de um caixeiro viajante ir em todas as cidades possíveis
	no menor custo possível de distância.

	A leitura será feita por um programa externo:
	CIDADE A | CIDADE B | Distância
		1         2           3
		1         3           4
		1         4           2
		2         1           5
		...

		então, a n-enésima cidade A, onde estamos no momento, irá para o resto
   das outras cidades (n-1 cidades possíveis). Este é um problema de análise
   combinatória com a relação do menor custo das distâncias.

	Além disso, escolhe-se no programa qual será a cidade de origem.

	Precisa-se no final do programa mostrar a rota e o custo.
*/

#include "item.h"
#include "pilha.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int cidadeA;
  int cidadeB;
  int distancia;
  // exatidão
} Aresta;



int main(int arcv, char *argc[]) {

  FILE *arq;
  arq = fopen(&argc[0][1], "r");
  if (arq == NULL) {
	printf("Erro ao abrir o arquivo \n");
	return -1;
  }

  int numCidades, cidadeOrigem, numArestas;

  // Ler nº de Cidades e a cidade de origem, que está na
  // linha seguinte.
  fscanf(arq, "%d", &numCidades);
  fscanf(arq, "%d", &cidadeOrigem);

  fscanf(arq, "%d", &numArestas);
  // Podemos usar um vetor, do tipo Arestas
  // para colocarmos o nº total de arestas.

  // E, além do mais, Aresta possui cidade A e B,
  // e a distância percorrida.

  Aresta arestas[numArestas];
  for (int i = 0; i < numArestas; i++) {
	fscanf(arq, "%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB,
		   &arestas[i].distancia);
	// agora todos estão "sincronizados"
  }
  // ja lemos tudo que tinhamos pra ler;
  fclose(arq);

  // PILHA melhorRota <-> ao encontrarmos uma solução local ótima
  // podemos empilhá-la; Nossos itens serão as cidades, claro ainda nao tenha
  // ficado claro

  PILHA *pilha, *melhorRota;

  pilha = pilha_criar();
  melhorRota = pilha_criar();

  bool visitadas[TAM] = {false};
  visitadas[cidadeOrigem] = true;
  ITEM *item = item_criar(cidadeOrigem, 0);
  pilha_empilhar(pilha, item);

	int menorCusto = INT_MAX; 
	// iniciamos com um valor muito grande para quando
	// encontrarmos qualquer valor, solução local, ela já ser "validada"

  // Função de permutar o resto das cidades em relação a ela
	// nela será chamada as funções de encontrarMelhorRota, CalcularCusto.

	//permutar();

	printf("Melhor rota: \n");
	// pilha_topo devolve um item, logo, precisamos pegar sua chave.
	pilha_print(melhorRota);
	printf("\n");
	printf("Menor custo: %d\n", menorCusto);
}

