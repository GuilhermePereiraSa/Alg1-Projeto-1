#ifndef PILHA_H

#define PILHA_H

#include "item.h"
#include <stdbool.h>

#define TAM 5200

typedef struct pilha {
  ITEM *item[TAM];
  int tamanho;
} PILHA;

PILHA *pilha_criar(void);
void pilha_apagar(PILHA **pilha);
bool pilha_vazia(PILHA *pilha);
bool pilha_cheia(PILHA *pilha);
int pilha_tamanho(PILHA *pilha);
ITEM *pilha_topo(PILHA *pilha);
bool pilha_empilhar(PILHA *pilha, ITEM *item);
ITEM *pilha_desempilhar(PILHA *pilha);
void pilha_limpar(PILHA *pilha);
void pilha_print(PILHA *pilha);
void pilha_inverter(PILHA *pilha);

#endif
