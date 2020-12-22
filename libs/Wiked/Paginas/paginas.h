#ifndef Paginas_h
#define Paginas_h

#include <stdio.h>
#include "../../GenList/genList.h"

ListaGen* inserePagina(ListaGen *lista, char *pagina, char *arquivo);

ListaGen* retiraPagina(ListaGen *lista, char *pagina);

ListaGen* insereContribuicao(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo);

ListaGen* retiraContribuicao(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo);

ListaGen* insereLink(ListaGen *lista, char *pagOrigem, char *pagDestino);

ListaGen* retiraLink(ListaGen *lista, char *pagOrigem, char *pagDestino);

void escrevePagina(ListaGen *lista, char *pagina);

void liberaPagina(ListaGen *lista);

#endif