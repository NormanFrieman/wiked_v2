#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "libs/GenList/genList.h"
#include "libs/Wiked/wiked.h"

// ================= FUNCOES RESPONSAVEIS PELA INTERPRETACAO INICIAL DO COMANDO =================
void InsereEditor(ListaGen *editores, FILE *file){
    char editor[60];

    fscanf(file, "%s", editor);
    printf("\n---> INSEREEDITOR %s\n", editor);

    editores = INSEREEDITOR(editores, editor);
}

void InserePagina(ListaGen *paginas, FILE *file){
    char pagina[60], outfile[60];

    fscanf(file, "%s", pagina);
    fscanf(file, "%s", outfile);
    printf("\n---> INSEREPAGINA %s %s\n", pagina, outfile);
    
    paginas = INSEREPAGINA(paginas, pagina, outfile);
}

void RetiraPagina(ListaGen *paginas, FILE *file){
    char pagina[60];

    fscanf(file, "%s", pagina);
    printf("\n---> RETIRAPAGINA %s\n", pagina);
    
    paginas = RETIRAPAGINA(paginas, pagina);
}

void InsereContribuicao(ListaGen *paginas, ListaGen *editores, FILE *file){
    char pagina[60], editor[60], arquivo[60];

    fscanf(file, "%s", pagina);
    fscanf(file, "%s", editor);
    fscanf(file, "%s", arquivo);
    printf("\n---> INSERECONTRIBUICAO %s %s %s\n", pagina, editor, arquivo);
    
    paginas = INSERECONTRIBUICAO(paginas, editores, pagina, editor, arquivo);
}

void RetiraContribuicao(ListaGen *paginas, ListaGen *editores, FILE *file){
    char pagina[60], editor[60], arquivo[60];

    fscanf(file, "%s", pagina);
    fscanf(file, "%s", editor);
    fscanf(file, "%s", arquivo);
    printf("\n---> RETIRACONTRIBUICAO %s %s %s\n", pagina, editor, arquivo);
    
    paginas = RETIRACONTRIBUICAO(paginas, editores, pagina, editor, arquivo);
}

void Fim(ListaGen *paginas, ListaGen *editores){
    printf("\n---> FIM\n");
    FIM(editores, paginas);
}
// =================    =================



// ================= INTERPRETACAO DOS COMANDOS =================
char* setInput(char *input){
    char aux[60] = "Input/";
    char *path;

    strcat(aux, input);
    path = strdup(aux);

    return path;
}

void eraseInput(){
    FILE *logs;
    logs = fopen("Output/log.txt", "w");
    fclose(logs);
}

void interpretarComando(ListaGen *paginas, ListaGen *editores, char *url){
    char comand[100];
    FILE *file;

    file = fopen(url, "r");

    if(file == NULL)
        printf("ERROR: NAO FOI POSSIVEL LER O ARQUIVO ");
    else{
        while(!feof(file)){
            fscanf(file, "%s", comand);
            if(strcmp("INSEREEDITOR", comand) == 0)
                InsereEditor(editores, file);
            
            else if(strcmp("INSEREPAGINA", comand) == 0)
                InserePagina(paginas, file);
            
            else if(strcmp("RETIRAPAGINA", comand) == 0)
                RetiraPagina(paginas, file);
            
            else if(strcmp("INSERECONTRIBUICAO", comand) == 0)
                InsereContribuicao(paginas, editores, file);
            
            else if(strcmp("RETIRACONTRIBUICAO", comand) == 0)
                RetiraContribuicao(paginas, editores, file);

            else if(strcmp("FIM", comand) == 0){
                Fim(paginas, editores);
                break;
            }
            
            else
                printf("Funcao %s nao suportada nesta versao do wikED!\n", comand);
            
        }
    }

    fclose(file);
}
// =================    =================



int main(int argc, char *argv[]){
    char *url;
    ListaGen *editores = criaLista();
    ListaGen *paginas = criaLista();

    eraseInput();

    url = setInput(argv[1]);
    interpretarComando(paginas, editores, url);

    free(url);

    return 0;
}