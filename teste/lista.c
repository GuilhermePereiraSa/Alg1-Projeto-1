#include "lista.h"
#include "item.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct lista_ {
  ITEM *lista[TAM_MAX];
  int inicio;
  int fim;
  int tamanho;
  bool ordenada;
};

ITEM *lista_frente(LISTA *lista);

LISTA *lista_criar(void);

void lista_apagar(LISTA **lista);

bool lista_cheia(LISTA *lista);
bool lista_inserir_fim(LISTA *lista, ITEM *item);
bool lista_inserir_meio(LISTA *lista, int pos, ITEM *item);
bool lista_vazia(LISTA *lista);
void lista_shiftar_fim(LISTA *lista, int pos);
int lista_busca_binaria(LISTA *lista, int x);

int lista_tamanho(LISTA *lista);

ITEM *lista_buscar(LISTA *lista, int indice);

int partition(LISTA *lista, int low, int high);
void quicksort(LISTA *lista, int low, int high);

int lista_tamanho(LISTA *lista){
  return lista->tamanho;
}


void lista_imprimir(LISTA *lista);

LISTA *lista_criar(void) {
  LISTA *lista = (LISTA *)malloc(sizeof(LISTA));
  if (lista != NULL) {
    lista->inicio = 0;
    lista->fim = 0;
    lista->tamanho = 0;
    //lista->ordenada = ordenada;
  }
  return lista;
}

bool lista_cheia(LISTA *lista) {
  return lista != NULL && lista->tamanho == TAM_MAX;
}

bool lista_inserir_fim(LISTA *lista, ITEM *item) {
  if (!lista_cheia(lista)) {
    lista->lista[lista->fim] = item;
    lista->fim++;
    lista->tamanho++;
    return true;
  }
  return false;
}

bool lista_inserir_posicao(LISTA *lista, int pos, ITEM *item) {
  if (!lista_cheia(lista) && pos <= lista->fim) {
    lista_shiftar_fim(lista, pos);
    lista->lista[pos] = item;
    lista->fim++;
    lista->tamanho++;
    return true;
  }
  return false;
}

void lista_shiftar_fim(LISTA *lista, int pos) {
  if (!lista_vazia(lista)) {
    for (int i = lista->fim - 1; i >= pos; i--) {
      lista->lista[i + 1] = lista->lista[i];
    }
  }
}

bool lista_inserir(LISTA *lista, ITEM *item) {
  if (!lista_cheia(lista)) {
    if (!lista->ordenada) {
      return lista_inserir_fim(lista, item);
    } else {
      int x = lista_busca_binaria(lista, item_get_chave(item));
      return lista_inserir_posicao(lista, x, item);
    }
  }
  return false;
}

bool lista_vazia(LISTA *lista) {
  return lista->tamanho == 0;
}

int lista_busca_binaria(LISTA *lista, int x) {
  int inf = 0, sup = lista->fim - 1;
  while (inf <= sup) {
    int meio = (sup + inf) / 2;
    if (item_get_chave(lista->lista[meio]) == x) {
      return meio;
    } else if (item_get_chave(lista->lista[meio]) < x) {
      inf = meio + 1;
    } else {
      sup = meio - 1;
    }
  }
  return -1;
}

ITEM *lista_frente(LISTA *lista) {
  return lista->lista[lista->inicio];
}

void lista_apagar(LISTA **lista) {
  for (int i = 0; i < (*lista)->fim; i++) {
    free((*lista)->lista[i]);
  }
  free(*lista);
  *lista = NULL;
}

void lista_imprimir(LISTA *lista) {
  for (int i = 0; i < lista->fim; i++) {
    printf("[%d]; ", item_get_chave(lista->lista[i]));
  }
  printf("\n");
}

int partition(LISTA *lista, int low, int high) {
  int pivot = item_get_chave(lista->lista[high]);
  int i = low - 1;
  for (int j = low; j < high; j++) {
    if (item_get_chave(lista->lista[j]) <= pivot) {
      i++;
      ITEM *temp = lista->lista[i];
      lista->lista[i] = lista->lista[j];
      lista->lista[j] = temp;
    }
  }
  ITEM *temp = lista->lista[i + 1];
  lista->lista[i + 1] = lista->lista[high];
  lista->lista[high] = temp;
  return i + 1;
}

void quicksort(LISTA *lista, int low, int high) {
  if (low < high) {
    int pi = partition(lista, low, high);
    quicksort(lista, low, pi - 1);
    quicksort(lista, pi + 1, high);
  }
}

// Função para obter o item de um índice específico na lista
ITEM *lista_buscar(LISTA *lista, int indice) {
    // Verifica se o índice é válido
    if (lista == NULL || indice < 0 || indice >= lista_tamanho(lista)) {
        return NULL;
    }

    // Acessa o item da lista no índice solicitado
    // Em uma lista sequencial, isso pode ser feito diretamente através de um vetor de itens.
    // Aqui assumimos que existe uma estrutura interna para armazenar os itens da lista.
    return lista->lista[indice];
}
