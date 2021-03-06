#ifndef Wiked_h
#define Wiked_h

#include <stdio.h>
#include "../GenList/genList.h"

ListaGen* INSEREEDITOR(ListaGen *lista, char *editor);

ListaGen* INSEREPAGINA(ListaGen *lista, char *pagina, char *arquivo);

ListaGen* RETIRAPAGINA(ListaGen *lista, char *pagina);

ListaGen* INSERECONTRIBUICAO(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo);

ListaGen* RETIRACONTRIBUICAO(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo);

ListaGen* INSERELINK(ListaGen *lista, char *pagOrigem, char *pagDestino);

ListaGen* RETIRALINK(ListaGen *lista, char *pagOrigem, char *pagDestino);

void IMPRIMEPAGINA(ListaGen *lista, char *pagina);

void IMPRIMEWIKED(ListaGen *lista);

void CAMINHO(ListaGen *lista, char *pagOrigem, char *pagDestino);

void FIM(ListaGen *editores, ListaGen *paginas);

#endif

/*
escreverLog                 OK!
INSEREPAGINA                OK!
RETIRAPAGINA                OK! 
INSEREEDITOR                OK!
INSERECONTRIBUICAO          OK!
RETIRACONTRIBUICAO          OK!
INSERELINK                  OK!
RETIRALINK                  OK!
CAMINHO
IMPRIMEPAGINA               OK!
IMPRIMEWIKED                OK!
FIM                         OK!
*/