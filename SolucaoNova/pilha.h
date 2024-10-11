#ifndef PILHA_H_
#define PILHA_H_

#include "item.h"

typedef struct pilha_ PILHA;

PILHA *pilha_criar(void);
bool pilha_empilhar(PILHA *pilha, ITEM *it);
ITEM *pilha_desempilhar(PILHA *pilha);
bool pilha_vazia(PILHA *pilha);
bool pilha_cheia(PILHA *pilha);
int pilha_tamanho(PILHA *pilha);
ITEM *pilha_topo(PILHA *pilha);
bool pilha_esvaziar(PILHA *pilha);
void pilha_apagar(PILHA **pilha);
void pilha_imprimir(PILHA *pilha);
void pilha_inverter(PILHA *pilha);
void pilha_transferir(PILHA *origem, PILHA *destino);

#endif
