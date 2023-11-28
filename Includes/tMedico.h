#ifndef TMEDICO_H
#define TMEDICO_H

#include "tPessoa.h"

typedef struct tMedico tMedico;

tMedico* criaMedico(tPessoa* infos, char* usuario, char* senha, char* crm);

void desalocaMedico(tMedico* medico);

#endif