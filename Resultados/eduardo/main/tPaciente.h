#ifndef TPACIENTE_H
#define TPACIENTE_H

#include "tPessoa.h"
#include "tLesao.h"

typedef struct tPaciente tPaciente;

tPaciente* criaPaciente(tPessoa* infos);

void desalocaPaciente(tPaciente* paciente);

tPessoa* obtemInfoPaciente(tPaciente* p);

void adicionaConsultaPaciente(tPaciente* p, int id);

int obtemIdadePaciente(tPaciente* p);

void adicionaPacienteBandoDeDados(tPaciente* p, FILE* pFile);

#endif