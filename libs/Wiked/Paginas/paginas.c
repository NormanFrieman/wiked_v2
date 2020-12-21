#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "paginas.h"
#include "../Editores/editor.h"
#include "Complementos/complementos.h"

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

    liberaComplemento(pag->contribuicoes);
    liberaComplemento(pag->historico);

    free(pag->nome);
    free(pag->outfile);
    free(pag);
}
// ===============  ===============

ListaGen* inserePagina(ListaGen *lista, char *pagina, char *arquivo){
    if(verificaLista(lista, comparaPagina, pagina) != NULL){
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

    printf("Paginas:\n");
    imprimeLista(lista, imprimePagina);

    return lista;
}

ListaGen* retiraPagina(ListaGen *lista, char *pagina){
    if(verificaLista(lista, comparaPagina, pagina) == NULL){
        printf("ERROR: PAGINA %s NAO EXISTE\n", pagina);
        return lista;
    }

    lista = retiraLista(lista, comparaPagina, destroiPagina, pagina);

    printf("Paginas:\n");
    imprimeLista(lista, imprimePagina);

    return lista;
}

ListaGen* insereContribuicao(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo){
    Pagina *pag = verificaLista(lista, comparaPagina, pagina);
    if(pag == NULL){
        printf("ERROR: PAGINA %s NAO EXISTE\n", pagina);
        return lista;
    }

    if(verificaEditor(editores, editor) == 0){
        printf("ERROR: EDITOR %s NAO EXISTE\n", editor);
        return 0;
    }

    pag->contribuicoes = insereComplemento(pag->contribuicoes, pagina, arquivo, editor, 0);
    pag->historico = insereComplemento(pag->historico, pagina, arquivo, editor, 1);

    return lista;
}

ListaGen* retiraContribuicao(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo){
    Pagina *pag = verificaLista(lista, comparaPagina, pagina);
    if(pag == NULL){
        printf("ERROR: PAGINA %s NAO EXISTE\n", pagina);
        return lista;
    }

    if(verificaEditor(editores, editor) == 0){
        printf("ERROR: EDITOR %s NAO EXISTE\n", editor);
        return 0;
    }

    pag->contribuicoes = retiraComplemento(pag->contribuicoes, pagina, arquivo, editor, 0);

    return lista;
}

void liberaPagina(ListaGen *lista){
    liberaLista(lista, destroiPagina);
}