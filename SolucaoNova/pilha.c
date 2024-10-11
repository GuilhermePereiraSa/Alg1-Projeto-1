#include "pilha.h"
#include "item.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct no_ NO;

struct no_ {
  ITEM *item;
  NO *proximo;
};

struct pilha_ {
  NO *topo;
  int tamanho;
};

// Protocolos das funções
PILHA *pilha_criar(void);
bool pilha_empilhar(PILHA *pilha, ITEM *item);
bool pilha_vazia(PILHA *pilha);
int pilha_tamanho(PILHA *pilha);
bool pilha_cheia(PILHA *pilha);
ITEM *pilha_desempilhar(PILHA *pilha);
ITEM *pilha_topo(PILHA *pilha);
void pilha_apagar(PILHA **pilha);
void pilha_imprimir(PILHA *pilha);
void inserir_fundo(PILHA *pilha, ITEM *item);
void pilha_inverter(PILHA *pilha);
bool pilha_esvaziar(PILHA *pilha);
void pilha_transferir(PILHA *origem, PILHA *destino);

// Função de cirar um nó
NO *no_criar(ITEM *item) {
  NO *novoNo = (NO *)malloc(sizeof(NO));
  if (novoNo == NULL) {
    fprintf(stderr, "Falta memoria\n");
    return NULL;
  }
  novoNo->item = item;
  novoNo->proximo = NULL;
  return novoNo;
}

// Função para criar uma pilha do zero
PILHA *pilha_criar(void) {
  PILHA *p = (PILHA *)malloc(sizeof(PILHA));
  if (p == NULL) {
    fprintf(stderr, "Erro ao alocar a pilha\n");
    return NULL;
  }
  p->topo = NULL;
  p->tamanho = 0;
  return p;
}

// Função para empilhar
bool pilha_empilhar(PILHA *pilha, ITEM *item) {
  if (pilha == NULL || item == NULL) {
    fprintf(stderr, "Pilha ou item não alocados\n");
    return false;
  }

  NO *aux = no_criar(item);
  if (aux == NULL) {
    return false;
  }
  aux->proximo = pilha->topo;
  pilha->topo = aux;
  pilha->tamanho++;
  return true;
}

// Função para verificar se a pilha está vázia
bool pilha_vazia(PILHA *p) {
  if (p == NULL) {
    fprintf(stderr, "Nao existe a pilha\n");
    return false;
  }

  // Se o topo for nulo, então não tem nada na pilha
  return p->topo == NULL;
}

// Função para retornar o tamanho da pilha
// O atributo de tamanho do TAD pilha não é visível ao cliente
int pilha_tamanho(PILHA *pilha) {
  if (pilha == NULL) {
    fprintf(stderr, "Pilha nao alocada\n");
    return -1;
  }
  return pilha->tamanho;
}

// Função para verificar se a pilha está cheia
bool pilha_cheia(PILHA *p) {
  NO *aux = no_criar(NULL);
  // Se o nó auxiliar criado for nulo, então toda memória está sendo usada
  return aux == NULL ? true : false;
}

// Função para desempilhar o item do topo, último adicionado
ITEM *pilha_desempilhar(PILHA *pilha) {
  if (pilha_vazia(pilha)) {
    fprintf(stderr, "Pilha vazia\n");
    return NULL;
  }

  NO *aux = pilha->topo;
  pilha->topo = aux->proximo;
  ITEM *item = aux->item;
  free(aux);
  pilha->tamanho--;
  return item;
}

// Função para retornar o item do topo
// Aqui o topo é onde está o último item adicionado.
ITEM *pilha_topo(PILHA *pilha) {
  if (pilha_vazia(pilha)) {
    fprintf(stderr, "Pilha vazia\n");
    return NULL;
  }
  return pilha->topo->item;
}

// Função para apagar a pilha por completo
void pilha_apagar(PILHA **p) {
  if (*p == NULL) {
    fprintf(stderr, "Pilha nao alocada\n");
    return;
  }
  while (!pilha_vazia(*p)) {
    pilha_desempilhar(*p);
  }
  free(*p);
  *p = NULL;
}

// Função para imprimir os itens da pilha sequencialmente
void pilha_imprimir(PILHA *p) {
  if (p == NULL) {
    fprintf(stderr, "Pilha nao alocada\n");
    return;
  }
  NO *n = p->topo;
  while (n != NULL) {
    printf("%d ", item_get_chave(n->item));
    n = n->proximo;
  }
  printf("\n");
}

// Função auxiliar para inverter a pilha
void inserir_fundo(PILHA *pilha, ITEM *item) {
  if (pilha == NULL) {
    fprintf(stderr, "Pilha nao alocada\n");
    return;
  }
  if (item == NULL) {
    fprintf(stderr, "Item nao alocado\n");
    return;
  }

  if (pilha_vazia(pilha)) {
    pilha_empilhar(pilha, item);
    return;
  }

  ITEM *aux = pilha_desempilhar(pilha);
  inserir_fundo(pilha, item);
  pilha_empilhar(pilha, aux);
}

// Função para inverter a pilha
void pilha_inverter(PILHA *pilha) {
  if (pilha == NULL) {
    fprintf(stderr, "Pilha nao alocada\n");
    return;
  }
  if (pilha_vazia(pilha)) {
    return;
  }
  ITEM *it = pilha_desempilhar(pilha);
  pilha_inverter(pilha);
  inserir_fundo(pilha, it);
}

// Função para esvaziar a pilha. Apagar todos os itens dela e deixá-la vázia
bool pilha_esvaziar(PILHA *pilha) {
  if (pilha == NULL) {
    fprintf(stderr, "Pilha nao alocada\n");
    return false;
  }
  ITEM *iAux;
  while (!pilha_vazia(pilha)) {
    iAux = pilha_desempilhar(pilha);
    item_apagar(&iAux);
  }
  return true;
}

// Função para transferir cópias das chaves de uma pilha à outra
void pilha_transferir(PILHA *origem, PILHA *destino) {
  if (origem != NULL && destino != NULL) {

    ITEM *temp[origem->tamanho];
    int tamanho = origem->tamanho;
    for (int i = 0; i < tamanho; i++)
      temp[i] = pilha_desempilhar(origem);

    pilha_esvaziar(destino);
    for (int i = tamanho - 1; i >= 0; i--) {
      pilha_empilhar(destino, temp[i]);
      // Empilha-se então a cópia da chave do item originalmente da pilha de
      // Origem para a de Destino
      pilha_empilhar(origem, item_criar(item_get_chave(temp[i]), NULL));
    }
  }
}
