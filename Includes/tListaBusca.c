#include "tListaBusca.h"

struct tListaBusca{
    int nPessoas;
    tPessoa** pessoas;
};

tListaBusca* criaListaBusca(){
    tListaBusca* l =(tListaBusca*)calloc(1, sizeof(tListaBusca));
    l->pessoas=NULL;
}

void adicionaListaBusca(tListaBusca* l, tPessoa* p){
    l->pessoas=(tPessoa**)realloc(l->pessoas,(l->nPessoas+1)*sizeof(tPessoa*));
    l->pessoas[l->nPessoas]=p;
    l->nPessoas++;
}

void desalocaListaBusca(void* dado){
    tListaBusca* l =(tListaBusca*)(dado);
    free(l->pessoas);
    free(l);
}

void imprimeTelaListaBusca(void* dado){
    tListaBusca* l =(tListaBusca*)(dado);
    for(int i=0; i<l->nPessoas;i++){
        printf("%d - %s (%s)\n", (i+1), obtemNomePessoa(l->pessoas[i]), obtemCpfPessoa(l->pessoas[i]));
    }
    printf("\n");
}

void imprimeArquivoListaBusca(void* dado, char* path){
    tListaBusca* l =(tListaBusca*)(dado);
    char nome[1030];
    sprintf(nome, "%s/lista_busca.txt", path);
    FILE* pFile = fopen(nome, "a+");
    for(int i=0; i<l->nPessoas;i++){
        fprintf(pFile, "%d - %s (%s)\n", (i+1), obtemNomePessoa(l->pessoas[i]), obtemCpfPessoa(l->pessoas[i]));
    }
    fprintf(pFile, "\n");
}