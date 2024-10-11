#include "cidade.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct estrada_ {
  int destino;
  int distancia;
  ESTRADA *proxima;
};

struct cidade_ {
  int id;
  ESTRADA *conexoes;
};

// Protocolos das funções
CIDADE *cidade_criar(int id);
ESTRADA *estrada_criar(int origem, int distancia);
bool adicionar_estrada(CIDADE *cidade, int destino, int dist);
ESTRADA *estrada_proxima(ESTRADA *estrada);
int estrada_distancia(ESTRADA *estrada);
int estrada_destino(ESTRADA *estrada);
ESTRADA *cidade_conexoes(CIDADE *cidade);
int cidade_id(CIDADE *cidade);

ESTRADA *estrada_criar(int origem, int distancia);

// Função para criar uma nova estrada
ESTRADA *estrada_criar(int origem, int distancia) {
  ESTRADA *nova_estrada = (ESTRADA *)malloc(sizeof(ESTRADA));
  if (nova_estrada == NULL) {
    fprintf(stderr, "Erro ao alocar memoria para a estrada\n");
    return NULL;
  }

  nova_estrada->destino = origem;
  nova_estrada->distancia = distancia;
  nova_estrada->proxima = NULL;
  return nova_estrada;
}

// Função para criarmos um laço entre as estradas
ESTRADA *estrada_proxima(ESTRADA *estrada) {
  if (estrada == NULL) {
    return NULL;
  }
  return estrada->proxima;
}

// Função para retornar o destino B, de uma estrada AB e vice-versa
int estrada_destino(ESTRADA *estrada) {
  if (estrada == NULL) {
    return -1;
  }
  return estrada->destino;
}

// Função para retornar a distância de uma estrada, AB = BA
int estrada_distancia(ESTRADA *estrada) {
  if (estrada == NULL) {
    return -1;
  }
  return estrada->distancia;
}

// Função para criar uma nova cidade
CIDADE *cidade_criar(int id) {
  CIDADE *nova_c = (CIDADE *)malloc(sizeof(CIDADE));
  if (nova_c == NULL) {
    fprintf(stderr, "Erro ao alocar memoria para a cidade\n");
    return NULL;
  }
  nova_c->id = id;
  nova_c->conexoes = NULL;
  return nova_c;
}

// Função para adicionar uma nova estrada
bool adicionar_estrada(CIDADE *cidade, int destino, int dist) {
  if (cidade == NULL) {
    fprintf(stderr, "Cidade nao alocada\n");
    return false;
  }
  ESTRADA *nova_estrada = estrada_criar(destino, dist);
  if (nova_estrada == NULL) {
    return false;
  }
  nova_estrada->proxima = cidade->conexoes;
  cidade->conexoes = nova_estrada;
  return true;
}


// Função que retorna se há associações/laço com a cidade
ESTRADA *cidade_conexoes(CIDADE *cidade) {
  if (cidade == NULL) {
    return NULL;
  }
  return cidade->conexoes;
}

// Função para retornar o id da cidade
int cidade_id(CIDADE *cidade) {
  if (cidade == NULL) {
    return -1;
  }
  return cidade->id;
}
