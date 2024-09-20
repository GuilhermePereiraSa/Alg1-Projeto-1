#include <stdlib.h>
#include <stdio.h>
#include "item.h"

struct item_{ 
        int chave;   //indexador
        void *dados; //ponteiro para o dado
};

ITEM *item_criar (int chave, void *dado){
          ITEM *item;
          
          item = (ITEM *) malloc(sizeof(ITEM));
          
          if (item != NULL){
             item->chave = chave;
             item->dados = dado;
             return(item);
          }
          return(NULL);
}

bool item_apagar(ITEM **item){
   if (*item != NULL){
      free (*item);
      *item = NULL; /*Boa pr�tica!*/
      return(true);
   }
   return(false);
}

int item_get_chave(ITEM *item){
    if (item != NULL)
      return(item->chave);
    exit(1);
}


bool item_set_chave(ITEM *item, int chave){
  if (item != NULL){
    item->chave = chave;
    return (true);
  }
  return (false);
}

void *item_get_dados(ITEM *item){
  if(item !=NULL)
    return(item->dados);
  return(NULL);
}
