#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "../paginas.h"
#include "../GenStruct/genStruct.h"
#include "../../Editores/editor.h"
#include "complementos.h"

// =============== FUNCOES AUXILIARES ===============

// ===============  ===============





// =============== FUNCOES PRINCIPAIS ===============
static ListaGen* insereContrib(ListaGen *lista, char *pagina, char *nome, char *info){
    if(lista == NULL)
        lista = criaLista();

    if(insereItem(lista, nome, info, 0) == 0)
        printf("ERROR: CONTRIBUICAO %s JA EXISTE NA PAGINA %s\n", nome, pagina);
    
    else{
        printf("Contribuicoes em %s\n", pagina);
        imprimeItens(lista);
    }

    return lista;
}
static ListaGen* retiraContrib(ListaGen *lista, char *pagina, char *nome, char *info){
    int condition = retiraItem(lista, nome, info, 1);
    if(condition == 0)
        printf("ERROR: CONTRIBUICAO %s NAO EXISTE NA PAGINA %s\n", nome, pagina);
    
    else if(condition == -1)
        printf("ERROR: EDITOR %s NAO TEM PERMISSAO PARA REMOVER A CONTRIBUICAO %s\n", info, nome);
    
    else{
        printf("Contribuicoes em %s\n", pagina);
        imprimeItens(lista);
    }

    return lista;
}
static ListaGen* insereHist(ListaGen *lista, char *pagina, char *nome, char *info){
    if(lista == NULL)
        lista = criaLista();

    if(insereItem(lista, nome, info, 0) != 0){
        printf("Historico em %s\n", pagina);
        imprimeItens(lista);
    }
    
    return lista;
}
static ListaGen* insereLink(ListaGen *lista, char *nome, char *info){
    return lista;
}
static ListaGen* retiraLink(ListaGen *lista, char *nome, char *info){
    return lista;
}
// ===============  ===============





// =============== FUNCOES DE INTERFACE ===============
ListaGen* insereComplemento(ListaGen *lista, char *pagina, char *nome, char *info, int code){
    if(code == 0)
        lista = insereContrib(lista, pagina, nome, info);
    
    else if(code == 1)
        lista = insereHist(lista, pagina, nome, info);
    
    else
        lista = insereLink(lista, nome, info);
    
    return lista; 
}

ListaGen* retiraComplemento(ListaGen *lista, char *pagina, char *nome, char *info, int code){
    if(code == 0)
        lista = retiraContrib(lista, pagina, nome, info);
    
    else
        lista = retiraLink(lista, nome, info);
}
// ===============  ===============