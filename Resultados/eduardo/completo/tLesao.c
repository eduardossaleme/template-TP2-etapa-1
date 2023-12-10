#include "tLesao.h"

struct tLesao{
    char rotulo[MAX_TAM_ROTULO];
    char diagnostico[MAX_TAM_DIAGNOSTICO];
    char parteCorpo[MAX_TAM_PCH];
    int tamanho, cirurgia, crioterapia, id;
};

tLesao* criaLesao(char* diagnostico, char* parteCorpo, int tamanho, int cirurgia, int crioterapia, int id, int n){
    tLesao* l=(tLesao*)calloc(1, sizeof(tLesao));
    strcpy(l->diagnostico, diagnostico);
    strcpy(l->parteCorpo, parteCorpo);
    l->tamanho=tamanho;
    l->cirurgia=cirurgia;
    l->crioterapia=crioterapia;
    l->id=id;
    sprintf(l->rotulo,"L%d", n);
    return l;
}

void desalocaLesao(tLesao* l){
    free(l);
}

void adcionaLesaoBancoDeDados(tLesao* l, FILE* pFile){
    fwrite(l, sizeof(tLesao), 1, pFile);
}

tLesao* leLesaoBancoDeDados(FILE* pFile){
    tLesao* l=(tLesao*)calloc(1, sizeof(tLesao));
    fread(l, sizeof(tLesao), 1, pFile);
    return l;
}

int necessitaCirurgiaLesao(tLesao* l){
    return l->cirurgia;
}

int necessitaCrioterapiaLesao(tLesao* l){
    return l->crioterapia;
}

char* obtemRotuloLesao(tLesao* l){
    return l->rotulo;
}

char* obtemParteCorpoLesao(tLesao* l){
    return l->parteCorpo;
}

char* obtemDiagnosticoLesao(tLesao* l){
    return l->diagnostico;
}

int obtemIdLesao(tLesao* l){
    return l->id;
}

int obtemTamanhoLesao(tLesao* l){
    return l->tamanho;
}