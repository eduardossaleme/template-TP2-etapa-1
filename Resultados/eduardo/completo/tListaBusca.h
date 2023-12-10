#ifndef TLISTABUSCA_H
#define TLISTABUSCA_H

#include "tPessoa.h"

typedef struct tListaBusca tListaBusca;

tListaBusca* criaListaBusca();

void adicionaListaBusca(tListaBusca* l, tPessoa* p);

void desalocaListaBusca(void* dado);

void imprimeTelaListaBusca(void* dado);

void imprimeArquivoListaBusca(void* dado, char* path);

#endif