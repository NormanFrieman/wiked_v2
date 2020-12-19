#ifndef ListaGenerica_h
#define ListaGenerica_h

#include <stdio.h>

typedef struct listaGen ListaGen;

ListaGen* criaLista(void);

ListaGen* insereLista(ListaGen *lista, void *item);

ListaGen* retiraLista(ListaGen *lista, int (*comparacao)(void *, void *), void (*liberaItem)(void *), void *key);

void* verificaLista(ListaGen *lista, int (*comparacao)(void *, void *), void *key);

void imprimeLista(ListaGen *lista, void (*imprime)(void *));

void liberaLista(ListaGen *lista, void (*liberaItem)(void *));

#endif