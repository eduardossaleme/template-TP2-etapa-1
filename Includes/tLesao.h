#ifndef TLESAO_H
#define TLESAO_H

#include "tPessoa.h"

#define MAX_TAM_DIAGNOSTICO 25
#define MAX_TAM_PCH 15
#define MAX_TAM_ROTULO 6

typedef struct tLesao tLesao;

tLesao* criaLesao(char* diagnostico, char* parteCorpo, int tamanho, int cirurgia, int crioterapia, int id, int n);

void desalocaLesao(tLesao* l);

#endif