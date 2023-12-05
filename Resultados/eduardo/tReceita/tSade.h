#ifndef TSADE_H
#define TSADE_H

#include "tMedico.h"
#include "tSecretario.h"
#include "tPaciente.h"
#include "tConsulta.h"
#include "tFila.h"
#include "tListaBusca.h"

typedef struct tSade tSade;

tSade* inicializaSade(char* path);

void leBancoDeDadosSecretarios(tSade* sade);

void cadastraSecretario(tSade* sade);

void criaBancoDeDadosSecretarios(tSade* sade);

void leBancoDeDadosPacientes(tSade* sade);

void cadastraPaciente(tSade* sade);

void criaBancoDeDadosPacientes(tSade* sade);

void leBancoDeDadosMedicos(tSade* sade);

void cadastraMedico(tSade* sade);

void criaBancoDeDadosMedicos(tSade* sade);

void realizaLogin(tSade* sade);

void desalocaSade(tSade* sade);

void menuSade(tSade* sade);

void criaBancoDeDados(tSade* sade);

void filaDeImpressao(tSade* sade);

void buscaPaciente(tSade* sade);

#endif