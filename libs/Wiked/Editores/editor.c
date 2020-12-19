#include <stdio.h>
#include "../../GenList/genList.h"
#include "string.h"

// =============== FUNCOES AUXILIARES ===============
static int comparaString(void *item1, void *item2){
    char *editor1 = (char *)item1;
    char *editor2 = (char *)item2;

    if(strcmp(editor1, editor2) == 0)
        return 1;
    
    return 0;
}
static void imprimeEditores(void *item){
    char *editor = (char *)item;

    printf("%s\n", editor);
}
// ===============  ===============

ListaGen* insereEditor(ListaGen *lista, char *editor){
    if(verificaLista(lista, comparaString, editor) != NULL){
        printf("ERROR: EDITOR %s JA EXISTE\n", editor);
        return lista;
    }
    
    lista = insereLista(lista, editor);

    printf("\nEditores:\n");
    imprimeLista(lista, imprimeEditores);

    return lista;
}

int verificaEditor(ListaGen *lista, char *nome){
    if(verificaLista(lista, comparaString, nome) != NULL)
        return 1;
    
    return 0;
}