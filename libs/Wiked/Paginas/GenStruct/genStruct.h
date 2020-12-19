#ifndef GenStruct_h
#define GenStruct_h

#include <stdio.h>

// GenStruct = Estrutura Genérica
typedef struct genstruct GenStruct;

GenStruct* criaGenStruct(char *nome, char *info);

char* retornaNomeGenStruct(GenStruct *generic);

void destroiGenStruct(GenStruct *generic);

#endif