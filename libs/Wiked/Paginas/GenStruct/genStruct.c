#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "genStruct.h"

// GenStruct = Estrutura Genérica
struct genstruct{
    char *nome;
    char *info;
};

GenStruct* criaGenStruct(char *nome, char *info){
    GenStruct *novaStruct = (GenStruct *)malloc(sizeof(GenStruct));

    novaStruct->nome = strdup(nome);
    novaStruct->info = strdup(info);

    return novaStruct;
}

char* retornaNomeGenStruct(GenStruct *generic){
    return generic->nome;
}

void destroiGenStruct(GenStruct *generic){
    free(generic->nome);
    free(generic->info);
    free(generic);
}

#endif