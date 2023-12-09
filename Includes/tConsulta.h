#ifndef TCONSULTA_H
#define TCONSULTA_H

#include "tMedico.h"

typedef struct tConsulta tConsulta;

tConsulta* criaConsulta(char* data, int diabetes, int fumante, int alergia, int cancer, char* tipoPele, char* crm, int id);

void adcionaLesaoConsulta(tConsulta* c, int id);

void adicionaConsultaBandoDeDados(tConsulta* c, FILE* pFile);

void desalocaConsulta(tConsulta* c);

#endif