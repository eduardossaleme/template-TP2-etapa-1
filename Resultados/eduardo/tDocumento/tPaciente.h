#ifndef TPACIENTE_H
#define TPACIENTE_H

#include "tPessoa.h"
#include "tLesao.h"

typedef struct tPaciente tPaciente;

tPaciente* criaPaciente(tPessoa* infos);

void desalocaPaciente(tPaciente* paciente);

tPessoa* obtemInfoPaciente(tPaciente* p);

int obtemIdadePaciente(tPaciente* p);

void adicionaPacienteBandoDeDados(tPaciente* p, FILE* pFile);

#endif