#ifndef TLESAO_H
#define TLESAO_H

#include "tPessoa.h"

#define MAX_TAM_DIAGNOSTICO 25
#define MAX_TAM_PCH 15
#define MAX_TAM_ROTULO 6

typedef struct tLesao tLesao;

tLesao* criaLesao(char* diagnostico, char* parteCorpo, int tamanho, int cirurgia, int crioterapia, int id, int n);

void desalocaLesao(tLesao* l);

void adcionaLesaoBancoDeDados(tLesao* l, FILE* pFile);

tLesao* leLesaoBancoDeDados(FILE* pFile);

int necessitaCirurgiaLesao(tLesao* l);

int necessitaCrioterapiaLesao(tLesao* l);

char* obtemRotuloLesao(tLesao* l);

char* obtemParteCorpoLesao(tLesao* l);

char* obtemDiagnosticoLesao(tLesao* l);

int obtemIdLesao(tLesao* l);

int obtemTamanhoLesao(tLesao* l);

#endif