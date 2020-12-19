#include <stdio.h>
#include "wiked.h"
#include "Editores/editor.h"

ListaGen* INSEREEDITOR(ListaGen *lista, char *editor){
    lista = insereEditor(lista, editor);

    return lista;
}