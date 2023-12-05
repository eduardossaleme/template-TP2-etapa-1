#ifndef TMEDICO_H
#define TMEDICO_H

#include "tPessoa.h"

#define MAX_TAM_CRM 13

typedef struct tMedico tMedico;

tMedico* criaMedico(tPessoa* infos, char* usuario, char* senha, char* crm);

void desalocaMedico(tMedico* medico);

char* obtemCrmMedico(tMedico* m);

tPessoa* obtemInfoMedico(tMedico* m);

char* obtemUsuarioMedico(tMedico* m);

char* obtemSenhaMedico(tMedico* m);

void adicionaMedicoBandoDeDados(tMedico* m, FILE* pFile);

#endif