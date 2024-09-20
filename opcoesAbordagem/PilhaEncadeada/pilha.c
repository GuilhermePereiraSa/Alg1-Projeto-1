#include <stdio.h>
#include <pilha.h>


struct no_{
    ITEM *item;
    NO *anterior;
};

struct pilha_{
    int tamanho;
    NO *topo;
};


PILHA* pilha_criar(void){
    PILHA *pilha = (PILHA*) malloc(sizeof(PILHA));

    if(pilha != NULL){
        pilha->topo = NULL;
        pilha->tamanho = 0;
        return pilha;
    }

    return NULL;
}

bool pilha_vazia(PILHA *pilha){
    if(pilha != NULL){
        return ((pilha->tamanho == 0) ? true : false);
    }
}

ITEM *pilha_topo(PILHA *pilha){
    return (!pilha_vazia(pilha) && pilha != NULL ) ? pilha->topo->item : NULL;
}

void pilha_apagar(PILHA **pilha){
    NO *paux;
    if(!pilha_vazia(pilha)){
        while((*pilha)->topo != NULL){
            paux = (*pilha)->topo;
            (*pilha)->topo = (*pilha)->topo->anterior;
            item_apagar(&paux->item);
            paux->anterior = NULL;
            free(paux);
            paux = NULL;
        }
    }
    free(*pilha);
    *pilha = NULL;
}

int pilha_tamanho(PILHA *pilha){
    return (pilha != NULL) ? pilha->tamanho : -1;
}

bool pilha_cheia(PILHA *pilha){
    if(pilha != NULL && !pilha_vazia(pilha)){
        NO *no = (NO*) malloc(sizeof(NO));
        if(no != NULL){
            free(no);
            return false;
        }
        return true;
    }
}

bool pilha_empilhar(PILHA *pilha, ITEM *item){
    NO* pnovo = (NO*) malloc(sizeof(NO));
    if(pnovo != NULL){
        pnovo->item = item;
        pnovo->anterior = pilha->topo;
        pilha->topo = pnovo;
        pilha->tamanho++;
        return true;
    }
    return false;
}


ITEM *pilha_desempilhar(PILHA *pilha){
    ITEM *iaux;
    NO *pno;
    if(!pilha_vazia(pilha)){
        iaux = pilha->topo->item;
        pno = pilha->topo;
        pilha->topo = pilha->topo->anterior;
        pno->anterior = NULL; free(pno); pno = NULL;
        pilha->tamanho--;
        return iaux;
    }
    return NULL;
}