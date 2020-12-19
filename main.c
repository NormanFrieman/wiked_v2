#include <stdio.h>
#include "libs/GenList/genList.h"
#include "libs/Wiked/wiked.h"

int main(int argc, char *argv[]){
    ListaGen *listaEditores = criaLista();
    ListaGen *listaPaginas = criaLista();

    int num1 = 1, num2 = 2;

    printf("\nINSEREEDITOR");
    listaEditores = INSEREEDITOR(listaEditores, "rob");
    printf("\nINSEREEDITOR");
    listaEditores = INSEREEDITOR(listaEditores, "rob2");

    printf("\nINSEREPAGINA");
    listaPaginas = INSEREPAGINA(listaPaginas, "Fisica", "fisica.txt");
    printf("\nINSEREPAGINA");
    listaPaginas = INSEREPAGINA(listaPaginas, "Matematica", "matematica.txt");
    printf("\nINSEREPAGINA");
    listaPaginas = INSEREPAGINA(listaPaginas, "Artes", "artes.txt");

    printf("\nRETIRAPAGINA");
    listaPaginas = RETIRAPAGINA(listaPaginas, "Matematica");

    printf("\nINSERECONTRIBUICAO");
    listaPaginas = INSERECONTRIBUICAO(listaPaginas, listaEditores, "Artes", "rob", "artes.txt");
    printf("\nINSERECONTRIBUICAO");
    listaPaginas = INSERECONTRIBUICAO(listaPaginas, listaEditores, "Artes", "rob", "artes.txt");

    FIM(listaEditores, listaPaginas);

    return 0;
}