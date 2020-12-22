#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "paginas.h"
#include "../Editores/editor.h"
#include "Complementos/complementos.h"
#include "GenStruct/genStruct.h"

typedef struct pagina Pagina;

struct pagina{
    char *nome;
    char *outfile;
    ListaGen *historico;
    ListaGen *contribuicoes;
    ListaGen *links;
};

// =============== FUNCOES AUXILIARES ===============
static void imprimePagina(void *item){
    Pagina *pag = (Pagina *)item;

    printf("%s\n", pag->nome);
    printf("  |-> arquivo: %s\n", pag->outfile);
}
static int comparaPagina(void *item1, void *item2){
    Pagina *pag = (Pagina *)item1;
    char *key = (char *)item2;

    if(strcmp(pag->nome, key) == 0)
        return 1;

    return 0;
}
static int removeLink(void *pagVerif, void *pagRem){
    Pagina *pag = (Pagina *)pagVerif;
    char *nome = (char *)pagRem;
    
    retiraItem(pag->links, nome, NULL, 0);

    return 0;
}
static void destroiPagina(void *item){
    Pagina *pag = (Pagina *)item;

    liberaComplemento(pag->contribuicoes);
    liberaComplemento(pag->historico);
    liberaComplemento(pag->links);

    free(pag->nome);
    free(pag->outfile);
    free(pag);
}
static void destroiChar(void *item){
    char *str = (char *)item;

    free(item);
}
char* setInput(char *input){
    char aux[60] = "Input/";
    char *path;

    strcat(aux, input);
    path = strdup(aux);

    return path;
}
static char* setOutput(char *output){
    char aux[60] = "Output/";
    char *path;

    strcat(aux, output);
    path = strdup(aux);

    return path;
}
static int writeContrib(void *gen, void *file){
    escreveComplemento(gen, file, 0);

    char letra;
    char *url = setInput(retornaNome(gen));
    FILE *inputContrib = fopen(url, "r");

    if(inputContrib == NULL)
        escreverLog("ERROR: IMPRESSAO FALHOU NA CONTRIBUICAO:", retornaNome(gen), NULL);
    
    else{
        while(!feof(inputContrib)){
            fscanf(inputContrib, "%c", &letra);
            fprintf(file, "%c", letra);
        }

        fprintf(file, "\n\n");
        fclose(inputContrib);
    }

    free(url);
    return 0;
}
static int writeHist(void *gen, void *file){
    escreveComplemento(gen, file, 1);

    return 0;
}
static int writeLink(void *gen, void *file){
    escreveComplemento(gen, file, 2);

    return 0;
}
static int printWiked(void *pag, void *item){
    Pagina *page = (Pagina *)pag;
    
    escrevePagina(NULL, page, page->nome, 1);

    return 0;
}
static int verificaRastro(void *item1, void *item2){
    char *str1 = (char *)item1;
    char *str2 = (char *)item2;

    if(strcmp(str1, str2) == 0)
        return 1;
    
    return 0;
}
static int path(ListaGen *lista, ListaGen *links, ListaGen *rastro, char *pagDestino){
    int code = 0, a = 0;
    char *pagTest = retornaInfoPorInt(links, a);

    while(pagTest != NULL){
        char *test = verificaLista(rastro, verificaRastro, pagTest);

        if(test == NULL){
            if(strcmp(pagTest, pagDestino) == 0)
                return 1;
            
            char *aux = strdup(pagTest);
            rastro = insereLista(rastro, aux);
            Pagina *page = verificaLista(lista, comparaPagina, pagTest);

            code = path(lista, page->links, rastro, pagDestino);

            if(code == 1)
                return 1;
        }

        a++;
        pagTest = retornaInfoPorInt(links, a);
    }

    return 0;
}
// ===============  ===============

ListaGen* inserePagina(ListaGen *lista, char *pagina, char *arquivo){
    if(verificaLista(lista, comparaPagina, pagina) != NULL){
        escreverLog("ERROR: PAGINA JA EXISTE:", pagina, NULL);
        return lista;
    }

    Pagina *novaPagina = (Pagina *)malloc(sizeof(Pagina));

    novaPagina->nome = strdup(pagina);
    novaPagina->outfile = strdup(arquivo);
    novaPagina->historico = NULL;
    novaPagina->contribuicoes = NULL;
    novaPagina->links = NULL;

    lista = insereLista(lista, novaPagina);

    printf("Paginas:\n");
    imprimeLista(lista, imprimePagina);

    return lista;
}

ListaGen* retiraPagina(ListaGen *lista, char *pagina){
    if(verificaLista(lista, comparaPagina, pagina) == NULL){
        escreverLog("ERROR: PAGINA NAO EXISTE:", pagina, NULL);
        return lista;
    }

    lista = retiraLista(lista, comparaPagina, destroiPagina, pagina);

    verificaLista(lista, removeLink, pagina);

    printf("Paginas:\n");
    imprimeLista(lista, imprimePagina);

    return lista;
}

ListaGen* insereContribuicao(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo){
    Pagina *pag = verificaLista(lista, comparaPagina, pagina);
    if(pag == NULL){
        escreverLog("ERROR: PAGINA NAO EXISTE:", pagina, NULL);
        return lista;
    }

    if(verificaEditor(editores, editor) == 0){
        escreverLog("ERROR: EDITOR NAO EXISTE:", editor, NULL);
        return 0;
    }

    pag->contribuicoes = insereComplemento(pag->contribuicoes, pagina, arquivo, editor, 0);
    pag->historico = insereComplemento(pag->historico, pagina, arquivo, editor, 1);

    return lista;
}

ListaGen* retiraContribuicao(ListaGen *lista, ListaGen *editores, char *pagina, char *editor, char *arquivo){
    Pagina *pag = verificaLista(lista, comparaPagina, pagina);
    if(pag == NULL){
        escreverLog("ERROR: PAGINA NAO EXISTE:", pagina, NULL);
        return lista;
    }

    if(verificaEditor(editores, editor) == 0){
        escreverLog("ERROR: EDITOR NAO EXISTE:", editor, NULL);
        return 0;
    }

    pag->contribuicoes = retiraComplemento(pag->contribuicoes, pagina, arquivo, editor, 0);

    return lista;
}

ListaGen* insereLink(ListaGen *lista, char *pagOrigem, char *pagDestino){
    Pagina *pagOri = verificaLista(lista, comparaPagina, pagOrigem);
    if(pagOri == NULL){
        escreverLog("ERROR: PAGINA ORIGEM NAO EXISTE:", pagOrigem, NULL);
        return lista;
    }

    Pagina *pagDest = verificaLista(lista, comparaPagina, pagDestino);
    if(pagDest == NULL){
        escreverLog("ERROR: PAGINA DESTINO NAO EXISTE:", pagDestino, NULL);
        return lista;
    }

    pagOri->links = insereComplemento(pagOri->links, NULL, pagDestino, pagDest->outfile, 2);

    return lista;
}

ListaGen* retiraLink(ListaGen *lista, char *pagOrigem, char *pagDestino){
    Pagina *pagOri = verificaLista(lista, comparaPagina, pagOrigem);
    if(pagOri == NULL){
        escreverLog("ERROR: PAGINA ORIGEM NAO EXISTE:", pagOrigem, NULL);
        return lista;
    }

    Pagina *pagDest = verificaLista(lista, comparaPagina, pagDestino);
    if(pagDest == NULL){
        escreverLog("ERROR: PAGINA DESTINO NAO EXISTE:", pagDestino, NULL);
        return lista;
    }

    pagOri->links = retiraComplemento(pagOri->links, NULL, pagDestino, pagDest->outfile, 2);

    return lista;
}

void escrevePagina(ListaGen *lista, void *page, char *pagina, int condition){
    Pagina *pag;

    if(condition == 0)
        pag = verificaLista(lista, comparaPagina, pagina);
    
    else
        pag = (Pagina *)page;

    if(pag == NULL)
        escreverLog("ERROR: PAGINA NAO EXISTE:", pagina, NULL);
    
    else{
        char *path = setOutput(pag->outfile);
        FILE *out = fopen(path, "w");

        if(out == NULL)
            escreverLog("ERRO: criacao de um novo txt inconcluido:", pagina, NULL);
        
        else{
            fprintf(out, "%s\n\n", pag->nome);

            fprintf(out, "--> Historico de contribuicoes\n");
            verificaLista(pag->historico, writeHist, out);

            fprintf(out, "\n--> Links\n");
            verificaLista(pag->links, writeLink, out);

            fprintf(out, "\n--> Textos\n\n");
            verificaLista(pag->contribuicoes, writeContrib, out);

            fclose(out);
        }

        free(path);
    }
}

void escreveWiked(ListaGen *lista){
    verificaLista(lista, printWiked, NULL);
}

void caminho(ListaGen *lista, char *pagOrigem, char *pagDestino){
    Pagina *pagOri = verificaLista(lista, comparaPagina, pagOrigem);
    Pagina *pagDest = verificaLista(lista, comparaPagina, pagDestino);
    
    if(pagOri == NULL)
        escreverLog("ERROR: PAGINA ORIGEM NAO EXISTE:", pagOrigem, NULL);

    else if(pagDest == NULL)
        escreverLog("ERROR: PAGINA DESTINO NAO EXISTE:", pagDestino, NULL);

    else{
        ListaGen *rastro = criaLista();
        
        int verif = path(lista, pagOri->links, rastro, pagDestino);
        liberaLista(rastro, destroiChar);

        if(verif == 1)
            escreverLog("HA CAMINHO ENTRE AS PAGINAS:", pagOrigem, pagDestino);
        
        else
            escreverLog("NAO HA CAMINHO ENTRE AS PAGINAS:", pagOrigem, pagDestino);
    }
}

void liberaPagina(ListaGen *lista){
    liberaLista(lista, destroiPagina);
}