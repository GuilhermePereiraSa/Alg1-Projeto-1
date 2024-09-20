#ifndef PILHA_H
    #define PILHA_H

    #include <stdbool.h>
    #include <item.h>

    typedef struct pilha_ PILHA;
    typedef struct no_ NO;

    PILHA *pilha_criar(void);
    void pilha_apagar(PILHA **pilha);
    bool pilha_vazia(PILHA *pilha);
    int pilha_tamanho(PILHA *pilha);
    ITEM *pilha_topo(PILHA *pilha);
    bool pilha_empilhar(PILHA *pilha, ITEM *item);
    ITEM *pilha_desempilhar(PILHA *pilha);

#endif