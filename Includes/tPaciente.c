#include "tPaciente.h"

struct tPaciente{
    tPessoa* info;
    int nLesoes, idade, diabetes, fumante, cancer, alergia;
    char tipoPele[3];
    tLesao** lesoes;
};

tPaciente* criaPaciente(tPessoa* infos){
    tPaciente* paciente = (tPaciente*)malloc(sizeof(tPaciente));
    paciente->info = infos;
    paciente->nLesoes = 0;
    paciente->lesoes = NULL;
    return paciente;
}

void desalocaPaciente(tPaciente* paciente){
    desalocaPessoa(paciente->info);

    for(int i=0;i<paciente->nLesoes;i++){
        desalocaLesao(paciente->lesoes[i]);
    }

    free(paciente->lesoes);

    free(paciente);
}