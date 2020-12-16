#include <stdio.h>
#include "libs/GenList/genList.h"

void imprime(void *dados){
    int *num = (int *)dados;
    printf("num: %d\n", *num);
}

int main(int argc, char *argv[]){
    ListaGen *lista = criaLista();

    int num1 = 1, num2 = 2;

    lista = insereLista(lista, &num1);
    lista = insereLista(lista, &num2);

    imprimeLista(lista, imprime);

    liberaLista(lista);

    return 0;
}