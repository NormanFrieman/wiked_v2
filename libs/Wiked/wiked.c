#include <stdio.h>
#include "wiked.h"
#include "Editores/editor.h"
#include "Paginas/paginas.h"

ListaGen* INSEREEDITOR(ListaGen *lista, char *editor){
    lista = insereEditor(lista, editor);

    return lista;
}

ListaGen* INSEREPAGINA(ListaGen *lista, char *pagina, char *arquivo){
    lista = inserePagina(lista, pagina, arquivo);

    return lista;
}

ListaGen* RETIRAPAGINA(ListaGen *lista, char *pagina){
    lista = retiraPagina(lista, pagina);

    return lista;
}

ListaGen* INSERECONTRIBUICAO(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo){
    lista = insereContribuicao(lista, editores, pagina, editor, arquivo);
}

ListaGen* RETIRACONTRIBUICAO(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo){
    lista = retiraContribuicao(lista, editores, pagina, editor, arquivo);
}

void FIM(ListaGen *editores, ListaGen *paginas){
    liberaEditores(editores);
    liberaPagina(paginas);
}