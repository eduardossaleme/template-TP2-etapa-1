#include "tRelatorioGeral.h"

struct tRelatorioGeral{
    int nPacientesAtendidos, masc, fem, outros, idadeMedia, tamLesoes, crioterapia, cirurgia, nLesoes;
};

tRelatorioGeral* criaRelatorioGeral(int nP, int masc, int fem, int out, int idade, int tamL, int crioterapia, int cirurgia, int nLesoes){
    tRelatorioGeral* r = (tRelatorioGeral*)calloc(1, sizeof(tRelatorioGeral));
    r->nPacientesAtendidos=nP;
    r->masc=masc;
    r->fem=fem;
    r->outros=out;
    r->idadeMedia=idade;
    r->tamLesoes=tamL;
    r->crioterapia=crioterapia;
    r->cirurgia=cirurgia;
    r->nLesoes=nLesoes;
    return r;
}

void imprimeNaTelaRelatorioGeral(void* dado){
    tRelatorioGeral* r = (tRelatorioGeral*)(dado);
    printf("NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->nPacientesAtendidos);
    printf("IDADE MEDIA: %d\n", r->idadeMedia);
    printf("DISTRIBUICAO POR GENERO:\n");
    printf("- FEMININO: %d\n", r->fem);
    printf("- MASCULINO: %d\n", r->masc);
    printf("- OUTROS: %d\n", r->outros);
    printf("TAMANHO MEDIO DAS LESOES: %d\n", r->tamLesoes);
    printf("NUMERO TOTAL DE LESOES: %d\n", r->nLesoes);
    printf("NUMERO TOTAL DE CIRURGIAS: %d\n", r->cirurgia);
    printf("NUMERO TOTAL DE CRIOTERAPIA: %d\n", r->crioterapia);
}

void imprimeArquivoRelatorioGeral(void* dado, char* path){
    tRelatorioGeral* r = (tRelatorioGeral*)(dado);
    if(dado==NULL) return;
    char nome[1030];
    sprintf(nome, "%s/relatorio_geral.txt", path);
    FILE* pFile = fopen(nome, "a+");
    fprintf(pFile, "NUMERO TOTAL DE PACIENTES ATENDIDOS: %d\n", r->nPacientesAtendidos);
    fprintf(pFile, "IDADE MEDIA: %d\n", r->idadeMedia);
    fprintf(pFile, "DISTRIBUICAO POR GENERO:\n");
    fprintf(pFile, "- FEMININO: %d\n", r->fem);
    fprintf(pFile, "- MASCULINO: %d\n", r->masc);
    fprintf(pFile, "- OUTROS: %d\n", r->outros);
    fprintf(pFile, "TAMANHO MEDIO DAS LESOES: %d\n", r->tamLesoes);
    fprintf(pFile, "NUMERO TOTAL DE LESOES: %d\n", r->nLesoes);
    fprintf(pFile, "NUMERO TOTAL DE CIRURGIAS: %d\n", r->cirurgia);
    fprintf(pFile, "NUMERO TOTAL DE CRIOTERAPIA: %d\n\n", r->crioterapia);
    fclose(pFile);
}

void desalocaRelatorioGeral(void* dado){
    tRelatorioGeral* r = (tRelatorioGeral*)(dado);
    free(r);
}