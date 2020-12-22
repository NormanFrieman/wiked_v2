#ifndef GenStruct_h
#define GenStruct_h

#include <stdio.h>
#include "../../../GenList/genList.h"

typedef struct generic Generic;

int insereItem(ListaGen *lista, char *nome, char *info, int ignore);

int retiraItem(ListaGen *lista, char *nome, char *info, int verificaInfo);

char* verificaItem(ListaGen *lista, char *key);

char* retornaNome(Generic *gen);

char* retornaInfo(Generic *gen);

char* retornaInfoPorInt(ListaGen *lista, int key);

void imprimeItens(ListaGen *lista);

void destroiGenStruct(ListaGen *lista);

#endif