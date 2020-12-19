#include <stdio.h>
#include "../../GenList/genList.h"
#include "string.h"

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

ListaGen* insereEditor(ListaGen *lista, char *editor){
    lista = insereLista(lista, editor);

    printf("\nEditores:\n");
    imprimeLista(lista, imprimeEditores);

    return lista;
}