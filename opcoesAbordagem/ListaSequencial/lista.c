#include "lista.h"
#include "item.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct lista_ {
  ITEM *lista[TAM];
  int inicio;
  int fim;
  int tamanho;
  bool ordenada;
};

LISTA *lista_criar(bool ordenada);
bool lista_cheia(LISTA *lista);
bool lista_inserir_fim(LISTA *lista, ITEM *item);
bool lista_inserir_meio(LISTA *lista, int pos, ITEM *item);
bool lista_vazia(LISTA *lista);

//  true ou false para parâmetro - ordenada ou não -> Inserção, remoção, busca
LISTA *lista_criar(bool ordenada) {
  LISTA *lista = (LISTA *)malloc(sizeof(LISTA));

  if (lista != NULL) {
    lista->fim = lista->inicio;
    lista->inicio = lista->fim;
    lista->tamanho = 0;

    return lista;
  }

  return NULL;
}

// Função que retorna se a lista está cheia ou não
bool lista_cheia(LISTA *lista) {
  if (lista != NULL)
    return lista->tamanho == TAM ? true : false;
  return false;
}

// não ordenada - \theta(1)
bool lista_inserir_fim(LISTA *lista, ITEM *item) {
  if (!lista_cheia(lista)) {
    lista->lista[lista->fim] = item;
    lista->fim++;
    lista->tamanho++;
    return true;
  }
  return false;
}

// inserção no meio
bool lista_inserir_meio(LISTA *lista, int pos, ITEM *item) {
  int i;
  if (!lista_cheia(lista) && (pos <= lista->fim - 1)) {

    for (i = lista->fim; i >= pos; i--) {
      lista->lista[i + 1] = lista->lista[i];
    }

    lista->lista[pos] = item;
    lista->fim++;
    lista->tamanho++;

    // deslocar os itens de i à n  p/ i+1 até n+1

    return true;
  }
  return false;
}

bool lista_inserir_posicao(LISTA *lista, int pos, ITEM *item) {
  if (!lista_cheia(lista) && (pos <= lista->fim - 1)) {
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

// ordenada ou nao
bool lista_inserir(LISTA *lista, ITEM *item) {
  if (!lista->ordenada) {
    return (lista_inserir_fim(lista, item));
  } else {
    int x = lista_busca_binaria(lista, item_get_chave(item));
    return lista_inserir_posicao(lista, x, item);
  }
  return false;
}

// Função para verificar se a lista é vázia
bool lista_vazia(LISTA *lista) { return lista->tamanho == 0 ? true : false; }

// Busca sequencial para uma lista não ordenada
int lista_busca_sequencial(LISTA *lista, int x) {
  int i;
  if (lista != NULL && !lista_vazia(lista)) {
    for (int i = 0; i < lista->fim; i++) {
      if (item_get_chave(lista->lista[i]) == x) {
        return i;
      }
    }
  }
  return -1;
}

// Busca sequencial otimizada pela ordenação
int lista_busca_sequencial_ordenada(LISTA *lista, int x) {
  int i = 0;

  if (!lista_vazia(lista) && lista != NULL) {
    while (item_get_chave(lista->lista[i]) < x) {
      i++;
      if (i >= lista->fim) {
        break;
      }
    }
    return i;
  } else {
    return -1;
  }
}


ITEM *lista_remover(LISTA *lista, int x) {
  // achando a chave -> retorna item
  int pos;
  if (!lista_vazia(lista)) {
    // Busca pelo item -> ordenação
    if (lista->ordenada) {
      int pos = lista_busca_binaria(lista, x);
    } else {
      int pos = lista_busca_sequencial(lista, x);
    }
    lista_shiftar_fim(lista, pos);
  }
}

int lista_busca_binaria(LISTA *lista, int x) {
  int inf = 0;
  int sup = lista->fim - 1;

  while (inf != sup) {
    int meio = (sup + inf) / 2;
    if (lista->lista[meio] == x) {
      return (meio + 1);
    }

    else if (lista->lista[meio] < x) {
      sup = meio - 1;
    }

    else if (lista->lista[meio] > x) {
      inf = meio + 1;
    }
  }
}

void quicksort(LISTA *lista, int low, int high) {

  int pi = partition(lista->lista, low, high);
  // antes e depois da partição
  quicksort(lista->lista, low, pi - 1);
  quicksort(lista->lista, pi + 1, high);
}

int partition(LISTA *lista, int low, int high) {
  int i = low - 1;
  int pivot = lista->lista[high];

  for (int j = low; j < high; j++) {
    if (lista->lista[j] <= pivot) {
      i++;
      int temp = lista->lista[j];
      lista->lista[j] = lista->lista[i];
      lista->lista[i] = temp;
    }
  }

  int temp = lista->lista[i + 1];
  lista->lista[i + 1] = lista->lista[high];
  lista->lista[high] = temp;

  return (i + 1);
}

void lista_imprimir(LISTA *lista) {
  for (int i = 0; i < lista->fim - 1; i++) {
    printf("%d\n", item_get_chave(lista->lista[i]));
  }
}

int main(void) {
  LISTA *lista;
  lista = lista_criar(0);

  int n;
  scanf("%d", &n);

  ITEM *item;
  int valor;
  for (int i = 0; i < n; i++) {
    scanf("%d", &valor);

    if (valor != NULL) {
      item = item_criar(valor, 0);
      lista_inserir_fim(lista, item);
    }
  }

  quicksort(lista, 0, n - 1);
  lista_imprimir(lista);

  return 0;
}
