#ifndef TBIOPSIA_H
#define TBIOPSIA_H

#include "tLesao.h"
#include "tMedico.h"

typedef struct tBiopsia tBiopsia;

tBiopsia* criaBiopsia(char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* crmMedico, char* data);

void adicionaLesaoBiopsia(tBiopsia* b, tLesao* l);

void imprimeNaTelaBiopsia(void* dado);

void imprimeEmArquivoBiopsia(void* dado, char* path);

void desalocaBiopsia(void* dado);

#endif