
#ifndef LISTA_H
	#define LISTA_H

	#define TAM_MAX 50000 /*estimativa do tamanho máximo da lista*/
	#define inicial 0
	#define ERRO -32000
	#define ORDENADA 1 // 0 = lista não ordenada, 1 = lista ordenada

	#include "item.h"

	typedef struct lista_ LISTA;

	LISTA *lista_criar(bool ordenada);
	bool lista_inserir(LISTA *lista, ITEM *item);
	void lista_apagar(LISTA **lista);

	int lista_tamanho(LISTA *lista);
	bool lista_vazia(LISTA *lista);
	bool lista_cheia(LISTA *lista);
	void lista_imprimir(LISTA *lista);

	ITEM *lista_buscar(LISTA *lista, int indice);
	  
#endif
