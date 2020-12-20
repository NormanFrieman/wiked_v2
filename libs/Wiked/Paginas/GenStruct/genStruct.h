#ifndef GenStruct_h
#define GenStruct_h

#include <stdio.h>
#include "../../../GenList/genList.h"

int insereItem(ListaGen *lista, char *nome, char *info, int ignore);

int retiraItem(ListaGen *lista, char *nome, char *info, int verificaInfo);

void imprimeItens(ListaGen *lista);

void destroiGenStruct(ListaGen *lista);

#endif