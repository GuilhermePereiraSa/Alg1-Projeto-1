/**
 * Problema do Caixeiro Viajante
 * 
 * Esse código resolve o problema do carteiro viajante utilizando duas abordagens:
 * 1. Algoritmo de força bruta com permutação para até 11 cidades.
 * 2. Algoritmo de backtracking para 12 ou mais cidades.
 * 
 * O programa gera todas as possíveis rotas que começam e terminam na cidade de origem,
 * calcula o custo de cada rota e determina a rota de menor custo.
 * 
 * @authors
 * - Augusto Fernandes Ildefonso
 * - Renan Trofino
 * - Guilherme Pereira de Sá
 * 
 * @date 11/10/2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "aresta.h"
#include "caminho.h"
#include "lista.h"

#define ORDENADA true

/**
 * Função para criar um vetor com todas as cidades para permutação.
 * Utilizada na abordagem de permutação (n < 12).
 * 
 * @param numCidade Número de cidades do problema
 * @return Vetor criado com as cidades
 */
int* cria_vetor_permutacao(int numCidade){
    int* vetor = (int*) malloc(sizeof(int) * numCidade);
    for(int i = 1; i <= numCidade; i++){
        vetor[i-1] = i;
    }
    return vetor;
}

/**
 * Função para criar um vetor com a cidade de origem fixada na primeira posição.
 * Utilizada na abordagem de backtracking (n >= 12).
 * 
 * @param numCidade Número de cidades do problema
 * @param cidadeOrigem Cidade de origem do percurso
 * @return Vetor criado com a cidade de origem fixada
 */
int* cria_vetor_backtracking(int numCidade, int cidadeOrigem) {
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
 * Função usada para realizar a permutação das cidades, responsável por fazer as trocas.
 * Utilizada tanto na abordagem de permutação quanto na de backtracking.
 * 
 * @param vetor É o vetor das cidades que será permutado
 * @param i Índice do vetor
 * @param j Índice do vetor
 */
void troca(int vetor[], int i, int j){
    int aux = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = aux;
}

/**
 * Essa função verifica se a última cidade do vetor possui uma aresta com a primeira,
 * permitindo retornar à cidade de origem.
 * 
 * @param lista Lista das arestas
 * @param vetor Vetor das cidades que será verificado
 * @param numCidades Número de cidades do problema
 * @param cidadeOrigem Cidade de origem do percurso
 * @param numArestas Número de arestas do problema
 * @return Retorna true se retorna à origem, false caso contrário
 */
bool volta_comeco(LISTA* lista, int vetor[], int numCidades, int cidadeOrigem, int numArestas){
    int ultimaCidade = vetor[numCidades - 1];
    int sentinela = 0;
    ARESTA* tmp_aresta;
    for(int i = 1; i <= numArestas; i++){
        tmp_aresta = lista_busca(lista, i);
        if(((cidadeOrigem == aresta_cidade_a(tmp_aresta)) && (ultimaCidade == aresta_cidade_b(tmp_aresta))) ||
           ((cidadeOrigem == aresta_cidade_b(tmp_aresta)) && (ultimaCidade == aresta_cidade_a(tmp_aresta)))){
            sentinela++;
        }
    }

    return sentinela > 0;
}

/**
 * Essa função calcula o custo/distância total de um percurso.
 * Utilizada na abordagem de permutação.
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
        for(int j = 1; j <= numArestas; j++){
            tmp_aresta = lista_busca(lista, j);
            if(((aresta_cidade_a(tmp_aresta) == cid_a) && (aresta_cidade_b(tmp_aresta) == cid_b)) ||
               ((aresta_cidade_a(tmp_aresta) == cid_b) && (aresta_cidade_b(tmp_aresta) == cid_a))){
                custo_atual += aresta_distancia(tmp_aresta);
                break; // Aresta encontrada, pode parar a busca
            }
        }		
    }

    return custo_atual;
}

/**
 * Essa função calcula o custo da aresta do último elemento para o primeiro (cidade de origem).
 * Utilizada na abordagem de permutação.
 * 
 * @param vetor Vetor do percurso/das cidades que será calculado
 * @param lista Lista das arestas do problema
 * @param numCidades Quantidade de cidades do problema
 * @param cidadeOrigem Cidade de origem/partida
 * @param numArestas Número de arestas do problema
 * @return Retorna o custo da aresta final
 */
int custo_aresta_final(int vetor[], LISTA* lista, int numCidades, int cidadeOrigem, int numArestas){
    int fim = vetor[numCidades-1];
    ARESTA* aresta_final = NULL;
    for(int i = 1; i <= numArestas; i++){
        ARESTA* tmp_aresta = lista_busca(lista, i);
        if(((aresta_cidade_a(tmp_aresta) == cidadeOrigem) && (aresta_cidade_b(tmp_aresta) == fim)) ||
           ((aresta_cidade_a(tmp_aresta) == fim) && (aresta_cidade_b(tmp_aresta) == cidadeOrigem))){
            aresta_final = tmp_aresta;
            break;
        }
    }

    if(aresta_final != NULL){
        return aresta_distancia(aresta_final);
    } else {
        return INT_MAX;
    }
}

/**
 * Essa função recursiva gera todas as permutações possíveis das cidades e encontra a de menor custo.
 * Utilizada na abordagem de permutação (n < 12).
 * 
 * @param vetor Vetor das cidades que será permutado
 * @param ini Índice inicial para permutação
 * @param fim Índice final para permutação
 * @param lista Lista das arestas do problema
 * @param numCidades Número de cidades do problema
 * @param cidadeOrigem Cidade de origem do percurso
 * @param numArestas Número de arestas do problema
 * @param caminho_menor_custo Estrutura para armazenar o caminho de menor custo
 */
void gera_caminhos_permutacao(int vetor[], int ini, int fim, LISTA* lista, int numCidades, int cidadeOrigem, int numArestas, CAMINHO* caminho_menor_custo){
    if(ini == fim){ 
        if(volta_comeco(lista, vetor, numCidades, cidadeOrigem, numArestas) && (vetor[0] == cidadeOrigem)){
            int custo_atual_caminho = calcula_custo_caminho(vetor, lista, numCidades, cidadeOrigem, numArestas);
            custo_atual_caminho += custo_aresta_final(vetor, lista, numCidades, cidadeOrigem, numArestas);

            if(custo_atual_caminho < caminho_get_custo(caminho_menor_custo)){
                caminho_set_custo(caminho_menor_custo, custo_atual_caminho);
                caminho_set_percurso(caminho_menor_custo, vetor, numCidades);
            }
        } 
    } else{
        for(int i = ini; i <= fim; i++){
            troca(vetor, ini, i);
            gera_caminhos_permutacao(vetor, ini + 1, fim, lista, numCidades, cidadeOrigem, numArestas, caminho_menor_custo);
            troca(vetor, ini, i);
        }
    }
}

/**
 * Essa função declara o vetor das cidades e chama a função para gerar todos os caminhos por permutação.
 * Utilizada na abordagem de permutação (n < 12).
 * 
 * @param lista_input Lista de arestas do problema
 * @param numCidades Número de cidades do problema
 * @param cidadeOrigem Cidade de origem/partida do problema
 * @param numArestas Número de arestas do problema
 * @param caminho_menor_custo Estrutura para armazenar o caminho de menor custo
 */
void busca_menor_custo_permutacao(LISTA* lista_input, int numCidades, int cidadeOrigem, int numArestas, CAMINHO* caminho_menor_custo){
    int* vet_cidades = cria_vetor_permutacao(numCidades);
    gera_caminhos_permutacao(vet_cidades, 0, numCidades-1, lista_input, numCidades, cidadeOrigem, numArestas, caminho_menor_custo);
    free(vet_cidades);
}

/**
 * Essa função recursiva é a responsável por gerar as permutações e calcular o menor caminho
 * utilizando a técnica de backtracking.
 * Utilizada na abordagem de backtracking (n >= 12).
 * 
 * @param vetor Vetor das cidades com a origem fixada
 * @param ini Índice do início do vetor para permutação
 * @param matriz Matriz de distâncias entre as cidades
 * @param numCidades Número de cidades do problema
 * @param custo_parcial Custo acumulado até o momento
 * @param melhor_custo Ponteiro para armazenar o melhor custo encontrado
 * @param melhor_percurso Vetor para armazenar o melhor percurso encontrado
 */
void backtracking(int vetor[], int ini, int matriz[][12], int numCidades, int custo_parcial, int* melhor_custo, int* melhor_percurso) {
    if (ini == numCidades) {
        // Fechando o ciclo, adicionando o custo de volta à cidade de origem
        if (matriz[vetor[numCidades - 1] - 1][vetor[0] - 1] != INT_MAX) {
            int custo_total = custo_parcial + matriz[vetor[numCidades - 1] - 1][vetor[0] - 1];
            if (custo_total < *melhor_custo) {
                *melhor_custo = custo_total;
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
 * Função para criar a matriz de distâncias entre as cidades.
 * 
 * @param lista_input Lista de arestas do problema
 * @param matriz Matriz de distâncias a ser preenchida
 * @param numArestas Número de arestas do problema
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
 * Função para medir o tempo de execução do backtracking.
 * 
 * @param func Ponteiro para a função de backtracking
 * @param vetor Vetor das cidades com a origem fixada
 * @param matriz Matriz de distâncias entre as cidades
 * @param numCidades Número de cidades do problema
 * @param custo_parcial Custo acumulado até o momento
 * @param melhor_custo Ponteiro para armazenar o melhor custo encontrado
 * @param melhor_percurso Vetor para armazenar o melhor percurso encontrado
 * @return Tempo gasto na execução em segundos
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

/**
 * Função para medir o tempo de execução da abordagem de permutação.
 * 
 * @param func Ponteiro para a função de geração de caminhos por permutação
 * @param lista_input Lista de arestas do problema
 * @param numCidades Número de cidades do problema
 * @param cidadeOrigem Cidade de origem do percurso
 * @param numArestas Número de arestas do problema
 * @param caminho_menor_custo Estrutura para armazenar o caminho de menor custo
 * @return Tempo gasto na execução em segundos
 */
double medir_tempo_permutacao(void (*func)(LISTA*, int, int, int, CAMINHO*), LISTA* lista_input, int numCidades, int cidadeOrigem, int numArestas, CAMINHO* caminho_menor_custo) {
    clock_t inicio, fim;
    double tempo_gasto;

    // Início da contagem de tempo
    inicio = clock();

    // Executa a função de permutação
    func(lista_input, numCidades, cidadeOrigem, numArestas, caminho_menor_custo);

    // Fim da contagem de tempo
    fim = clock();

    // Calcula o tempo gasto
    tempo_gasto = ((double) (fim - inicio)) / CLOCKS_PER_SEC;
    return tempo_gasto;
}

/**
 * Função principal que realiza a leitura dos dados, escolhe a abordagem apropriada (permutação ou backtracking),
 * executa a busca pelo menor custo e imprime os resultados.
 */
int main(void){
    int numCidades, cidadeOrigem, numArestas;
    
    // Lendo o número de cidades, cidade de origem, e o número de arestas
    scanf("%d %d %d", &numCidades, &cidadeOrigem, &numArestas);

    // Alocação para armazenar o melhor percurso
    int* vet_caminho_menor_custo = (int*) calloc(numCidades, sizeof(int));

    // Inicialização da estrutura para armazenar o menor custo e percurso
    CAMINHO* caminho_menor_custo = caminho_inicializa(INT_MAX, vet_caminho_menor_custo, numCidades);

    // Criação e preenchimento da lista de arestas
    LISTA* lista_input = lista_criar(ORDENADA);
    int tmp_cidade_A, tmp_cidade_B, tmp_distancia;
    for(int i = 1; i <= numArestas; i++){
        scanf("%d %d %d", &tmp_cidade_A, &tmp_cidade_B, &tmp_distancia);
        lista_inserir(lista_input, aresta_criar(tmp_cidade_A, tmp_cidade_B, tmp_distancia, i));
    }

    // Variáveis para a abordagem de backtracking
    int melhor_custo_backtracking = INT_MAX;
    int* melhor_percurso_backtracking = (int*) calloc(numCidades, sizeof(int));

    // Variáveis para a abordagem de permutação
    double tempo_permutacao = 0.0;
    double tempo_backtracking = 0.0;

    if(numCidades < 12){
        // Abordagem de permutação para menos de 12 cidades
        tempo_permutacao = medir_tempo_permutacao(busca_menor_custo_permutacao, lista_input, numCidades, cidadeOrigem, numArestas, caminho_menor_custo);
    }
    else{
        // Abordagem de backtracking para 12 ou mais cidades

        // Criação da matriz de distâncias
        int matriz[12][12];
        cria_matriz_distancias(lista_input, matriz, numArestas);

        // Criação do vetor de cidades com a origem fixada
        int* vet_cidades_backtracking = cria_vetor_backtracking(numCidades, cidadeOrigem);

        // Mede o tempo do backtracking
        tempo_backtracking = medir_tempo_backtracking(vet_cidades_backtracking, matriz, numCidades, &melhor_custo_backtracking, melhor_percurso_backtracking);

        // Atualiza o caminho_menor_custo com os resultados do backtracking
        if(melhor_custo_backtracking < caminho_get_custo(caminho_menor_custo)){
            caminho_set_custo(caminho_menor_custo, melhor_custo_backtracking);
            caminho_set_percurso(caminho_menor_custo, melhor_percurso_backtracking, numCidades);
        }

        // Liberação de memória do vetor de backtracking
        free(vet_cidades_backtracking);
    }

    // Imprime os resultados
    printf("Cidade de origem: %d\n", cidadeOrigem);
    printf("O custo do menor caminho é: %d\n", caminho_get_custo(caminho_menor_custo));
    printf("O percurso é: ");
    for(int i = 0; i < numCidades; i++){
        printf("%d-", caminho_get_percurso(caminho_menor_custo)[i]);
    }
    printf("%d\n", cidadeOrigem);

    // Imprime o tempo de execução conforme a abordagem utilizada
    if(numCidades < 12){
        printf("Tempo de execução pela abordagem de permutação: %.6f segundos\n", tempo_permutacao);
    }
    else{
        printf("Tempo de execução pela abordagem de backtracking: %.6f segundos\n", tempo_backtracking);
    }

    free(melhor_percurso_backtracking);
    free(vet_caminho_menor_custo);
    lista_apagar(&lista_input);

    return 0;
}
