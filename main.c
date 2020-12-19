#include <stdio.h>
#include "libs/GenList/genList.h"
#include "libs/Wiked/wiked.h"

int main(int argc, char *argv[]){
    ListaGen *listaEditores = criaLista();

    int num1 = 1, num2 = 2;

    listaEditores = INSEREEDITOR(listaEditores, "rob");
    listaEditores = INSEREEDITOR(listaEditores, "rob2");

    

    liberaLista(listaEditores);

    return 0;
}