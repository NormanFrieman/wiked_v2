#ifndef Complementos_h
#define Complementos_h

#include <stdio.h>
#include "../../../GenList/genList.h"

/*
0 -> CONTRIBUICAO
1 -> HISTORICO
2 -> LINK
*/

ListaGen* insereComplemento(ListaGen *lista, char *pagina, char *nome, char *info, int code);


ListaGen* retiraComplemento(ListaGen *lista, char *pagina, char *nome, char *info, int code);

#endif