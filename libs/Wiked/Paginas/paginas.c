#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "paginas.h"
#include "GenStruct/genStruct.h"
#include "../Editores/editor.h"

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
    
    destroiGenStruct(pag->historico);
    destroiGenStruct(pag->contribuicoes);
    destroiGenStruct(pag->links);

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

    if(pag->contribuicoes == NULL)
        pag->contribuicoes = criaLista();
    
    if(pag->historico == NULL)
        pag->historico = criaLista();

    if(insereItem(pag->contribuicoes, arquivo, editor, 0) == 0){
        printf("ERROR: CONTRIBUICAO %s JA EXISTE NA PAGINA %s\n", arquivo, pagina);
        return lista;
    }

    insereItem(pag->historico, editor, arquivo, 1);

    printf("Contribuicoes em %s\n", pagina);
    imprimeItens(pag->contribuicoes);

    printf("Historico de %s\n", pagina);
    imprimeItens(pag->historico);

    return lista;
}

void liberaPagina(ListaGen *lista){
    liberaLista(lista, destroiPagina);
}