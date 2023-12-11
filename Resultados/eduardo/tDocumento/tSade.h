#ifndef TSADE_H
#define TSADE_H

#include "tMedico.h"
#include "tSecretario.h"
#include "tPaciente.h"
#include "tConsulta.h"
#include "tLesao.h"
#include "tFila.h"
#include "tListaBusca.h"
#include "tReceita.h"
#include "tBiopsia.h"
#include "tEncaminhamento.h"

typedef struct tSade tSade;

tSade* inicializaSade(char* path);

void leBancoDeDadosSecretarios(tSade* sade);

void cadastraSecretario(tSade* sade);

void criaBancoDeDadosSecretarios(tSade* sade);

void leBancoDeDadosPacientes(tSade* sade);

void cadastraPaciente(tSade* sade);

void criaBancoDeDadosPacientes(tSade* sade);

void leBancoDeDadosMedicos(tSade* sade);

void leBancoDeDadosConsulta(tSade* sade);

void criaBancoDeDadosConsulta(tSade* sade);

void leBancoDeDadosLesoes(tSade* sade);

void criaBancoDeDadosLesoes(tSade* sade);

void cadastraMedico(tSade* sade);

void criaBancoDeDadosMedicos(tSade* sade);

void realizaLogin(tSade* sade);

void desalocaSade(tSade* sade);

void menuSade(tSade* sade);

void criaBancoDeDados(tSade* sade);

void filaDeImpressao(tSade* sade);

void buscaPaciente(tSade* sade);

int cpfJaExistente(tSade* sade, char* cpf);

void iniciaConsulta(tSade* sade);

void realizaConsulta(tSade* sade, tPaciente* paciente);

void cadastraLesao(tSade* sade, int n);

void geraReceita(tSade* sade, tPaciente* p, char* data);

void geraBiopsia(tSade* sade, tPaciente* p, char* data);

void geraEncaminhamento(tSade* sade, tPaciente* p, char* data);

#endif