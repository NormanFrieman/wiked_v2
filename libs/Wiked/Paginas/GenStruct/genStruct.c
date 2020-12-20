#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "genStruct.h"

// GenStruct = Estrutura Genérica
typedef struct generic Generic;

struct generic{
    char *nome;
    char *info;
};

// =============== FUNCOES AUXILIARES ===============
static int comparaItem(void *item1, void *item2){
    Generic *gen = (Generic *)item1;
    char *item = (char *)item2;
    
    if(strcmp(gen->nome, item) == 0)
        return 1;
    
    return 0;
}
static void destroiItem(void *item){
    Generic *gen = (Generic *)item;
    if(gen != NULL){
        free(gen->nome);
        free(gen->info);
        free(gen);
    }
}
static void imprimeItem(void *item){
    Generic *gen = (Generic *)item;

    printf("  |-> priority: %s\n", gen->nome);
    printf("  |-> info: %s\n", gen->info);
}
// ===============  ===============

// ignore -> define se é pra ignorar a existencia do item na lista ou não
int insereItem(ListaGen *lista, char *nome, char *info, int ignore){
    if(ignore == 0)
        if(verificaLista(lista, comparaItem, nome) != NULL)
            return 0;
    
    
    Generic *novaGen = (Generic *)malloc(sizeof(Generic));

    novaGen->nome = strdup(nome);
    novaGen->info = strdup(info);

    lista = insereLista(lista, novaGen);

    return 1;
}

// verificaInfo -> verifica se o char info é igual ao info da estrutura Generic
// return 0 -> nao existe
// return 1 -> removido
// return -1 -> nao possui permissao
int retiraItem(ListaGen *lista, char *nome, char *info, int verificaInfo){
    Generic *gen = verificaLista(lista, comparaItem, nome);
    if(gen == NULL)
        return 0;
    
    if(verificaInfo == 1)
        if(strcmp(gen->info, info) != 0)
            return -1;

    lista = retiraLista(lista, comparaItem, destroiItem, nome);

    return 1;
}

void imprimeItens(ListaGen *lista){
    imprimeLista(lista, imprimeItem);
}

void destroiGenStruct(ListaGen *lista){
    liberaLista(lista, destroiItem);
}