#include <stdio.h>
#include <stdlib.h>
#include "genList.h"

typedef struct cel Celula;

struct listaGen{
    Celula *Prim;
    Celula *Ult;
};

struct cel{
    void *item;
    Celula *prox;
};

ListaGen* criaLista(void){
    ListaGen *novaLista = (ListaGen *)malloc(sizeof(ListaGen));
    novaLista->Prim = NULL;
    novaLista->Ult = NULL;

    return novaLista;
}

ListaGen* insereLista(ListaGen *lista, void *item){
    Celula *novoItem = (Celula *)malloc(sizeof(Celula));
    novoItem->item = item;
    novoItem->prox = NULL;

    if(lista->Prim == NULL)
        lista->Prim = lista->Ult = novoItem;
    else{
        lista->Ult->prox = novoItem;
        lista->Ult = novoItem;
    }

    return lista;
}

ListaGen* retiraLista(ListaGen *lista, int (*comparacao)(void *, void *), void (*liberaItem)(void *), void *key){
    Celula *p = lista->Prim;
    Celula *ant = NULL;

    while(p != NULL && comparacao(p->item, key) != 1){
        ant = p;
        p = p->prox;
    }

    if(p == NULL)
        return lista;

    if(lista->Prim == p)
        lista->Prim = lista->Prim->prox;
    else
        ant->prox = p->prox;
    
    if(liberaItem != NULL)
        liberaItem(p->item);
    free(p);

    return lista;
}

void* verificaLista(ListaGen *lista, int (*comparacao)(void *, void *), void *key){
    Celula *p = lista->Prim;
    Celula *ant = NULL;
    
    while(p != NULL && comparacao(p->item, key) != 1){
        ant = p;
        p = p->prox;
    }

    if(p == NULL)
        return NULL;

    return p->item;
}

void imprimeLista(ListaGen *lista, void (*imprime)(void *)){
    Celula *p = lista->Prim;

    while(p != NULL){
        imprime(p->item);
        p = p->prox;
    }
}

void liberaLista(ListaGen *lista, void (*liberaItem)(void *)){
    if(lista != NULL){
        Celula *p = lista->Prim;
        Celula *ant = NULL;
        
        while(p != NULL){
            ant = p;
            p = p->prox;
            if(liberaItem != NULL)
                liberaItem(ant->item);
            free(ant);
        }

        free(lista);
    }
}