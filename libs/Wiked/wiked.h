#ifndef Wiked_h
#define Wiked_h

#include <stdio.h>
#include "../GenList/genList.h"

ListaGen* INSEREEDITOR(ListaGen *lista, char *editor);

ListaGen* INSEREPAGINA(ListaGen *lista, char *pagina, char *arquivo);

ListaGen* RETIRAPAGINA(ListaGen *lista, char *pagina);

ListaGen* INSERECONTRIBUICAO(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo);

ListaGen* RETIRACONTRIBUICAO(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo);

void FIM(ListaGen *editores, ListaGen *paginas);

#endif

/*
INSEREPAGINA                OK!
RETIRAPAGINA                OK!
INSEREEDITOR                OK!
INSERECONTRIBUICAO          OK!
RETIRACONTRIBUICAO          OK!
INSERELINK
RETIRALINK
CAMINHO
IMPRIMEPAGINA
IMPRIMEWIKED
FIM
*/