#include "tPaciente.h"

struct tPaciente{
    tPessoa* info;
    int nConsultas,idade;
    int *idConsulta;
};

tPaciente* criaPaciente(tPessoa* infos){
    tPaciente* paciente = (tPaciente*)calloc(1,sizeof(tPaciente));
    paciente->info = infos;
    paciente->nConsultas = 0;
    paciente->idConsulta=NULL;
    return paciente;
}

void desalocaPaciente(tPaciente* paciente){
    desalocaPessoa(paciente->info);
    if(paciente->idConsulta!=NULL) free(paciente->idConsulta);
    free(paciente);
}

tPessoa* obtemInfoPaciente(tPaciente* p){
    return p->info;
}

void adicionaConsultaPaciente(tPaciente* p, int id){
        p->idConsulta=(int*)realloc(p->idConsulta,(p->nConsultas+1)*sizeof(int));
        p->idConsulta[p->nConsultas]=id;
        p->nConsultas++;
}

int obtemIdadePaciente(tPaciente* p){
    return p->idade;
}

int obtemNConsultasPaciente(tPaciente* p){
    return p->nConsultas;
}

void adicionaPacienteBandoDeDados(tPaciente* p, FILE* pFile){
    escrecePessoaBinario(p->info, pFile);
    fwrite(&p->nConsultas, sizeof(int), 1, pFile);
    for(int i=0;i<p->nConsultas;i++){
        fwrite(&p->idConsulta[i], sizeof(int), 1, pFile);
    }
}