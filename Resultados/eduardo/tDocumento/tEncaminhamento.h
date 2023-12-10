#ifndef TENCAMINHAMENTO_H
#define TENCAMINHAMENTO_H

#include "tMedico.h"

#define MAX_TAM_MOTIVO 301
#define MAX_TAM_ESPECIALIDADE 51

typedef struct tEncaminhamento tEncaminhamento;

tEncaminhamento* criaEncaminhamento(char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* crmMedico, char* data, char* especialidade, char* motivo);

void imprimeNaTelaEncaminhamento(void* dado);

void imprimeEmArquivoEncaminhamento(void* dado, char* path);

void desalocaEncaminhamento(void* dado);

#endif