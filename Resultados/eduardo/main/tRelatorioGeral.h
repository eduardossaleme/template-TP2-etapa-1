#ifndef TRELATORIOGERAL_H
#define TRELATORIOGERAL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct tRelatorioGeral tRelatorioGeral;

tRelatorioGeral* criaRelatorioGeral(int nP, int masc, int fem, int out, int idade, int tamL, int crioterapia, int cirurgia, int nLesoes);

void imprimeNaTelaRelatorioGeral(void* dado);

void imprimeArquivoRelatorioGeral(void* dado, char* path);

void desalocaRelatorioGeral(void* dado);

#endif