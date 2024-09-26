#include <limits.h>
typedef struct{
    int cidadeA;
    int cidadeB;
    int distancia;
}Aresta;

void troca(int *a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}


// Função para encontrar a distância entre duas cidades
int encontrarDistancia(Aresta arestas[], int numArestas, int cidadeA, int cidadeB) {
    for (int i = 0; i < numArestas; i++) {
        if ((arestas[i].cidadeA == cidadeA && arestas[i].cidadeB == cidadeB) ||
            (arestas[i].cidadeA == cidadeB && arestas[i].cidadeB == cidadeA)) {
            return arestas[i].distancia;
        }
    }
    return INT_MAX; // Retorna valor grande se não houver conexão
}

// Função para calcular o custo de uma rota completa
int calcularCusto(Aresta arestas[], int numArestas, int cidades[], int numCidades) {
    int custo = 0;
    for (int i = 0; i < numCidades - 1; i++) {
        int distancia = encontrarDistancia(arestas, numArestas, cidades[i], cidades[i + 1]);
        if (distancia == INT_MAX)
            return INT_MAX; // Se não houver conexão, rota inválida
        custo += distancia;
    }
    // Adiciona o custo de retorno à cidade de origem
    int distanciaRetorno = encontrarDistancia(arestas, numArestas, cidades[numCidades - 1], cidades[0]);
    if (distanciaRetorno == INT_MAX)
        return INT_MAX;
    custo += distanciaRetorno;
    return custo;
}

// Função para gerar todas as permutações de cidades
void permutacao(Aresta arestas[], int numArestas, int cidades[], int inicio, int numCidades, int *menorCusto, int melhorRota[]) {
    if (inicio == numCidades) {
        int custo = calcularCusto(arestas, numArestas, cidades, numCidades);
        if (custo < *menorCusto) {
            *menorCusto = custo;
            for (int i = 0; i < numCidades; i++) {
                melhorRota[i] = cidades[i]; // Atualiza a melhor rota
            }
        }
    } else {
        for (int i = inicio; i < numCidades; i++) {
            troca(&cidades[inicio], &cidades[i]); // Faz a troca para gerar permutação
            permutacao(arestas, numArestas, cidades, inicio + 1, numCidades, menorCusto, melhorRota);
            troca(&cidades[inicio], &cidades[i]); // Volta à configuração original (backtrack implícito)
        }
    }
}


