#include "../EDs/item.h"
#include "../EDs/lista.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

/*
Definir uma struct para auxiliar com as arestas
*/
typedef struct {
    int cidadeA;
    int cidadeB;
    int distancia;
} Aresta;

// Função para encontrar a distância entre duas cidades
int encontrar_distancia(Aresta arestas[], int numArestas, int cidadeA, int cidadeB) {
    for (int i = 0; i < numArestas; i++) {
        // Lembrar que, se há dois vertices, A e B, a aresta AB = BA, é a mesma aresta.
        if ((arestas[i].cidadeA == cidadeA && arestas[i].cidadeB == cidadeB) ||
            (arestas[i].cidadeA == cidadeB && arestas[i].cidadeB == cidadeA)) {
            return arestas[i].distancia;
        }
    }
    return INT_MAX; // Retorna um valor grande se não houver conexão entre as cidades
}

// Função para calcular o custo de uma rota completa
int calcular_custo(Aresta arestas[], int numArestas, LISTA* lista) {
    int custo = 0;

    for (int i = 0; i < lista_tamanho(lista) -1; i++) {
        ITEM* atual = lista_get_posicao(lista, i);
        ITEM* proxima = lista_get_posicao(lista, i+1);

        //Calcula a distancia das duas cidades
        int dist = encontrar_distancia(arestas, numArestas, item_get_chave(atual), item_get_chave(proxima));

        if (dist == INT_MAX) {
            return(INT_MAX); // Se não houver conexão, rota inválida
        }

        custo += dist;
    }

    // Adiciona o custo de retorno à cidade de origem
    ITEM *ultima = lista_get_posicao(lista, lista_tamanho(lista)-1);
    ITEM *origem = lista_get_posicao(lista, 0);

    // Profundidade da árvore gerada até o momento
    int retorno = encontrar_distancia(arestas, numArestas, item_get_chave(ultima), item_get_chave(origem));
    if (retorno == INT_MAX) {
        return INT_MAX;
    }
        
    custo += retorno;
    return custo;
}

// Função para gerar todas as permutações de cidades de forma iterativa
void permutar(Aresta arestas[], int numArestas, LISTA* melhorRota, int* menorCusto, int numCidades) {
    LISTA* rota =  lista_criar(); // Cria uma lista para armazenar a rota

    // Array para controlar cidades visitadas
    bool* visitado = (bool*) malloc(numCidades * sizeof(bool));
    if (visitado == NULL) {
        exit(1);
    }

    // Coloca todas como não visitadas.
    for (int i = 0; i < numCidades; i++) {
        visitado[i] = false;
    }

     // Começa pela cidade de origem (cidade 0)
    ITEM *origem = item_criar(0, 0); // Cidade 0 com peso 0
    lista_inserir(rota, origem);
    visitado[0] = true;

    while (!lista_vazia(rota)) {
        ITEM* atual = lista_remover_ultimo(rota); 
        visitado[item_get_chave(atual)] = false; //Ajusta o vetor de visitados
        
        if (lista_tamanho(rota) == numCidades - 1) {
            // Se uma rota completa é formada

            // Então calcula-se o custo total desta rota
            int custo = calcular_custo(arestas, numArestas, rota);
            if (custo < *menorCusto) {
                *menorCusto = custo; // Atualiza a melhor rota

                // Depois segue a melhor rota (ramo) 
                for (int i = 0; i < lista_tamanho(rota); i++) {
                    ITEM *cidade = lista_get_posicao(rota, i);
                    lista_inserir(melhorRota, cidade);
                }
            }
            continue;
        }

        // Expandir o caminho atual, "gerar" novas rotas, explorar as que ainda não foram exploradas
        for (int i = numCidades - 1; i >= 0; i--) {
            if (!visitado[i]) {
                visitado[i] = true;
                ITEM *cidade = item_criar(i, 0); // Criar item cidade
                lista_inserir(rota, cidade);
            }
        }
    }

    lista_apagar(&rota);
}

/*
Função principal que coordena o programa.
*/
int main(void) {
    int numCidades, cidadeOrigem, numArestas;
    scanf("%d %d %d", &numCidades, &cidadeOrigem, &numArestas);

    Aresta* arestas = (Aresta*) malloc(numArestas * sizeof(Aresta));
    if (arestas == NULL) {
        exit(1);
    }

    //Ler arestas 
    for (int i = 0; i < numArestas; i++) {
        scanf("%d %d %d", &arestas[i].cidadeA, &arestas[i].cidadeB, &arestas[i].distancia);
    }

    LISTA* melhorRota = lista_criar();
    int menorCusto = INT_MAX;

    // Chama a função de permutação para encontrar a melhor rota
    permutar(arestas, numArestas, melhorRota, &menorCusto, numCidades);

    printf("Melhor rota: \n");
    lista_print(melhorRota);
    printf("\nMenor custo: %d\n", menorCusto);

    lista_apagar(&melhorRota);
    free(arestas);

    return 0;
}