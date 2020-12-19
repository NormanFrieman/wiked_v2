#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "paginas.h"
#include "GenStruct/genStruct.h"

typedef struct pagina Pagina;

struct pagina{
    char *nome;
    char *outfile;
    ListaGen *historico;
    ListaGen *contribuicoes;
    ListaGen *links;
};

// =============== FUNCOES AUXILIARES ===============
static void imprimePagina(void *item){
    Pagina *pag = (Pagina *)item;

    printf("%s\n", pag->nome);
    printf("  |-> arquivo: %s\n", pag->outfile);
}
static int comparaPagina(void *item1, void *item2){
    Pagina *pag = (Pagina *)item1;
    char *key = (char *)item2;

    if(strcmp(pag->nome, key) == 0)
        return 1;

    return 0;
}
static void destroiPagina(void *item){
    Pagina *pag = (Pagina *)item;
    
    free(pag->nome);
    free(pag->outfile);
    free(pag);
}
// ===============  ===============

ListaGen* inserePagina(ListaGen *lista, char *pagina, char *arquivo){
    Pagina *test = verificaLista(lista, comparaPagina, pagina);

    if(test != NULL){
        printf("ERROR: PAGINA %s JA EXISTE\n", pagina);
        return lista;
    }

    Pagina *novaPagina = (Pagina *)malloc(sizeof(Pagina));

    novaPagina->nome = strdup(pagina);
    novaPagina->outfile = strdup(arquivo);
    novaPagina->historico = NULL;
    novaPagina->contribuicoes = NULL;
    novaPagina->links = NULL;

    lista = insereLista(lista, novaPagina);

    printf("\nPaginas:\n");
    imprimeLista(lista, imprimePagina);

    return lista;
}

ListaGen* retiraPagina(ListaGen *lista, char *pagina){
    lista = retiraLista(lista, comparaPagina, destroiPagina, pagina);

    printf("\nPaginas:\n");
    imprimeLista(lista, imprimePagina);

    return lista;
}
/*
ListaGen* insereContribuicao(ListaGen *lista, char *editor, char *arquivo){    
    GenStruct *novaStruct = criaGenStruct(arquivo, editor);

    if(lista->contribuicoes == NULL)
        lista->contribuicoes = criaLista();

    lista->contribuicoes = insereLista(lista->contribuicoes, novaStruct);

    return lista;
}
*/
void liberaPagina(ListaGen *lista){
    liberaLista(lista, destroiPagina);
}