#include "tLesao.h"

struct tLesao{
    char rotulo[MAX_TAM_ROTULO];
    char diagnostico[MAX_TAM_DIAGNOSTICO];
    char parteCorpo[MAX_TAM_PCH];
    int tamanho, cirurgia, crioterapia, id;
};

tLesao* criaLesao(char* diagnostico, char* parteCorpo, int tamanho, int cirurgia, int crioterapia, int id, int n){
    tLesao* l=(tLesao*)calloc(1, sizeof(tLesao));
    strcmp(l->diagnostico, diagnostico);
    strcmp(l->parteCorpo, parteCorpo);
    l->tamanho=tamanho;
    l->cirurgia=cirurgia;
    l->crioterapia=crioterapia;
    l->id=id;
    sprintf(l->rotulo,"L%d", n);
}

void desalocaLesao(tLesao* l){
    free(l);
}