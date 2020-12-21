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
        escreverLog("ERROR: CONTRIBUICAO JA EXISTE NA PAGINA:", nome, pagina);
    
    else{
        printf("Contribuicoes em %s\n", pagina);
        imprimeItens(lista);
    }

    return lista;
}
static ListaGen* retiraContrib(ListaGen *lista, char *pagina, char *nome, char *info){
    int condition = retiraItem(lista, nome, info, 1);
    if(condition == 0)
        escreverLog("ERROR: CONTRIBUICAO NAO EXISTE NA PAGINA:", nome, pagina);
    
    else if(condition == -1)
        escreverLog("ERROR: EDITOR NAO TEM PERMISSAO PARA REMOVER A CONTRIBUICAO:", info, nome);
    
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
static ListaGen* insereL(ListaGen *lista, char *nome, char *info){
    if(lista == NULL)
        lista = criaLista();
    
    if(insereItem(lista, nome, info, 0) == 0)
        escreverLog("ERROR: LINK JA EXISTE NA PAGINA:", nome, NULL);
    
    else{
        printf("Links em %s\n", nome);
        imprimeItens(lista);
    }

    return lista;
}
static ListaGen* retiraL(ListaGen *lista, char *nome, char *info){
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
        lista = insereL(lista, nome, info);
    
    return lista; 
}

ListaGen* retiraComplemento(ListaGen *lista, char *pagina, char *nome, char *info, int code){
    if(code == 0)
        lista = retiraContrib(lista, pagina, nome, info);
    
    else
        lista = retiraL(lista, nome, info);
}

void liberaComplemento(ListaGen *lista){
    destroiGenStruct(lista);
}

void escreverLog(char *mensagem, char *str1, char *str2){
    FILE *logs = fopen("Output/log.txt", "a");

    if(logs == NULL){
        printf("ERROR: NAO FOI POSSIVEL ABRIR O ARQUIVO log.txt\n");
    }else{
        if(str1 == NULL && str2 == NULL){
            fprintf(logs, "%s\n", mensagem);
            printf("***** %s *****\n", mensagem);
        }else if(str1 != NULL && str2 == NULL){
            fprintf(logs, "%s %s\n", mensagem, str1);
            printf("***** %s %s *****\n", mensagem, str1);
        }else{
            fprintf(logs, "%s %s para %s\n", mensagem, str1, str2);
            printf("***** %s %s para %s *****\n", mensagem, str1, str2);
        }

        fclose(logs);
    }
}
// ===============  ===============