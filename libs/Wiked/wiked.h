#ifndef Wiked_h
#define Wiked_h

#include <stdio.h>
#include "../GenList/genList.h"

ListaGen* INSEREEDITOR(ListaGen *lista, char *editor);

ListaGen* INSEREPAGINA(ListaGen *lista, char *pagina, char *arquivo);

ListaGen* RETIRAPAGINA(ListaGen *lista, char *pagina);

//ListaGen* INSERECONTRIBUICAO(ListaGen *lista, char *editor, char *arquivo);

void FIM(ListaGen *editores, ListaGen *paginas);

#endif

/*
INSEREPAGINA                OK!
RETIRAPAGINA                QUASE OK! (falta contribuicao, link e historico)
INSEREEDITOR                OK!
INSERECONTRIBUICAO          
RETIRACONTRIBUICAO
INSERELINK
RETIRALINK
CAMINHO
IMPRIMEPAGINA
IMPRIMEWIKED
FIM
*/