/**
 * Problema do Caixeiro Viajante
 * 
 * Esse código resolve o problema do carteiro viajante usando um algoritmo de força bruta, que gera todas os possíveis percursos e filtra os percursos que cumprem
 * as regras de sempre voltar para a cidade de início e que a cidade inicial do percurso gerado é a cidade de origem informada. A partir desse filtro ele compara os 
 * percursos obtidos e armazena sempre o valor do percurso com menor custo.
 * Ele faz o uso de uma função recursiva para realizar as permutações.
 * 
 * @author Augusto Fernandes Ildefonso
 * @author Renan Trofino
 * @author Guilherme Pereira de Sá
 * 
 * @date 11/10/2024
 */

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
 * 
 * @param numCidade Número de cidades do problema
 * @return Retorna o vetor criado com as cidades
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
 * 
 * @param vetor É o vetor das cidades que será permutado
 * @param i Indice do vetor
 * @param j Indice do vetor
 */
void troca(int vetor[], int i, int j){
	int aux = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = aux;
}

/**
 * Essa função verifica que a última cidade do vetor possui uma aresta com a primeira, permitindo ele retornar ao começo
 * 
 * @param lista Lista das arestas
 * @param vetor Vetor das cidades que será permutado
 * @param numCidades Número de cidades do problema
 * @param cidadeOrigem Cidade de origem do percurso
 * @param numArestas Número de arestas do problema
 * @return Retorna true se ela volta ao começo e false se não volta
 */
bool volta_comeco(LISTA* lista, int vetor[], int numCidades, int cidadeOrigem, int numArestas){
	int ultimaCidade = vetor[numCidades - 1];
	int sentinela = 0;
	ARESTA* tmp_aresta;
	for(int i = 1; i <= numArestas; i++){
		tmp_aresta = lista_busca(lista, i);
		if(((cidadeOrigem == aresta_cidade_a(tmp_aresta)) && (ultimaCidade == aresta_cidade_b(tmp_aresta))) || ((cidadeOrigem == aresta_cidade_b(tmp_aresta)) && (ultimaCidade == aresta_cidade_a(tmp_aresta)))){
			sentinela++;
		}
	}

	if(sentinela == 0){
		return false;
	} else{
		return true;
	}
	
}

/**
 * Essa função calcula o custo/distância total de um percurso
 * 
 * @param vetor Vetor do percurso/das cidades que será calculado
 * @param lista Lista das arestas do problema
 * @param numCidades Quantidade de cidades do problema
 * @param cidadeOrigem Cidade de origem/partida
 * @param numArestas Número de arestas do problema
 * @return Retorna o custo do percurso
 */
int calcula_custo_caminho(int vetor[], LISTA* lista, int numCidades, int cidadeOrigem, int numArestas){
	int custo_atual = 0;
	for(int i = 0; i < numCidades; i++){
		int cid_a, cid_b;
		if(i == numCidades - 1){
			cid_a = vetor[i];
			cid_b = vetor[0];
		} else{
			cid_a = vetor[i];
			cid_b = vetor[i+1];
		}

		ARESTA* tmp_aresta;
		for(int j = 1; j <=numArestas; j++){
			tmp_aresta = lista_busca(lista, j);
			if(((aresta_cidade_a(tmp_aresta) == cid_a) && (aresta_cidade_b(tmp_aresta) == cid_b)) || ((aresta_cidade_a(tmp_aresta) == cid_b) && (aresta_cidade_b(tmp_aresta) == cid_a))){
				custo_atual+= aresta_distancia(tmp_aresta);
			}
		}		
	}

	return custo_atual;
}

/**
 * Essa função calcula o custo da aresta do penúltimo elemento para o último (que é a cidade de origem)
 * 
 * @param vetor Vetor do percurso/das cidades que será calculado
 * @param lista Lista das arestas do problema
 * @param numCidades Quantidade de cidades do problema
 * @param cidadeOrigem Cidade de origem/partida
 * @param numArestas Número de arestas do problema
 */
int custo_aresta_final(int vetor[], LISTA* lista, int numCidades, int cidadeOrigem, int numArestas){
	int fim = vetor[numCidades-1];
	ARESTA* aresta_final;
	for(int i = 1; i <= numArestas; i++){
		aresta_final = lista_busca(lista, i);
		if(((aresta_cidade_a(aresta_final) == cidadeOrigem) && (aresta_cidade_b(aresta_final) == fim)) || ((aresta_cidade_a(aresta_final) == fim) && (aresta_cidade_b(aresta_final) == cidadeOrigem))){
			break;
		}
	}
	return aresta_distancia(aresta_final);
}

/**
 * Essa função recursiva é a responsável por formar os vetores que representam as possibilidades de percurso e também escolhe o vetor de menor custo
 * 
 * @param vetor Vetor do percurso/das cidades que será calculado
 * @param ini Índice do início do vetor
 * @param fim Índice do fim do vetor
 * @param lista Lista das arestas do problema
 * @param numCidades Número de cidades do problema
 * @param cidadeOrigem Cidade de origem do percurso
 * @param numArestas Número de arestas do problema
 * @param caminho_menor_custo É o caminho que resolverá o problema e tem o menor custo dentre todas as possibilidades
 */
void gera_caminhos(int vetor[], int ini, int fim, LISTA* lista, int numCidades, int cidadeOrigem, int numArestas, CAMINHO* caminho_menor_custo){
	if(ini == fim){ 
		if((volta_comeco(lista, vetor, numCidades, cidadeOrigem, numArestas)) && (vetor[0] == cidadeOrigem)){
			int custo_atual_caminho;
			custo_atual_caminho = calcula_custo_caminho(vetor, lista, numCidades, cidadeOrigem, numArestas);
			custo_atual_caminho += custo_aresta_final(vetor, lista, numCidades, cidadeOrigem, numArestas);

			if(custo_atual_caminho < caminho_get_custo(caminho_menor_custo)){
				caminho_set_custo(caminho_menor_custo, custo_atual_caminho);
				caminho_set_percurso(caminho_menor_custo, vetor, numCidades);
			}
			
		} 
	} else{
		for(int i = ini; i <= fim; i++){
			troca(vetor, ini, i);
			gera_caminhos(vetor, ini + 1, fim, lista, numCidades, cidadeOrigem, numArestas, caminho_menor_custo);
			troca(vetor, ini, i);
		}
	}
}

/**
 * Essa função declara o vetor das cidades e chama a função para gerar todos os caminhos
 * 
 * @param lista_input Lista de arestas do problema
 * @param numCidades Número de cidades do problema
 * @param cidadeOrigem Cidade de origem/partida do problema
 * @param numArestas Número de arestas do problema
 * @param caminho_menor_custo É o caminho que resolverá o problema e tem o menor custo dentre todas as possibilidades
 */
void busca_menor_custo(LISTA* lista_input, int numCidades, int cidadeOrigem, int numArestas, CAMINHO* caminho_menor_custo){
	int* vet_cidades = cria_vetor(numCidades);

	gera_caminhos(vet_cidades, 0, numCidades-1, lista_input, numCidades, cidadeOrigem, numArestas, caminho_menor_custo);
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

	busca_menor_custo(lista_input, numCidades, cidadeOrigem, numArestas, caminho_menor_custo);

	vet_caminho_menor_custo = caminho_get_percurso(caminho_menor_custo);

	printf("O custo do menor caminho e: %d\n", caminho_get_custo(caminho_menor_custo));
	printf("O percurso e: ");
	for(int i = 0; i < numCidades; i++){
		printf("%d-", vet_caminho_menor_custo[i]);
	}
	printf("%d\n", cidadeOrigem);

	return 0;
}