#include "tPaciente.h"

struct tPaciente{
    tPessoa* info;
    int nConsultas, idade;
    int *idConsulta;
};

tPaciente* criaPaciente(tPessoa* infos){
    tPaciente* paciente = (tPaciente*)calloc(1,sizeof(tPaciente));
    paciente->info = infos;
    paciente->nConsultas = 0;
    return paciente;
}

void desalocaPaciente(tPaciente* paciente){
    desalocaPessoa(paciente->info);
    free(paciente);
}

tPessoa* obtemInfoPaciente(tPaciente* p){
    return p->info;
}

int obtemIdadePaciente(tPaciente* p){
    return p->idade;
}

void adicionaPacienteBandoDeDados(tPaciente* p, FILE* pFile){
    escrecePessoaBinario(p->info, pFile);
}