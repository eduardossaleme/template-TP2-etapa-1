#include "tPaciente.h"

struct tPaciente{
    tPessoa* info;
    int nLesoes, idade, diabetes, fumante, cancer, alergia;
    char tipoPele[3];
};

tPaciente* criaPaciente(tPessoa* infos){
    tPaciente* paciente = (tPaciente*)malloc(sizeof(tPaciente));
    paciente->info = infos;
    paciente->nLesoes = 0;
    return paciente;
}

void desalocaPaciente(tPaciente* paciente){
    desalocaPessoa(paciente->info);
    free(paciente);
}

tPessoa* obtemInfoPaciente(tPaciente* p){
    return p->info;
}

char* obtemTipoPelePaciente(tPaciente* p){
    return p->tipoPele;
}

int obtemIdadePaciente(tPaciente* p){
    return p->idade;
}

void adicionaPacienteBandoDeDados(tPaciente* p, FILE* pFile){
    fwrite(obtemNomePessoa(p->info), sizeof(char), MAX_TAM_NOME, pFile);
    fwrite(obtemCpfPessoa(p->info), sizeof(char), MAX_TAM_CPF, pFile);
    fwrite(obtemDataPessoa(p->info), sizeof(char), MAX_TAM_DATA, pFile);
    fwrite(obtemTelefonePessoa(p->info), sizeof(char), MAX_TAM_TELEFONE, pFile);
    fwrite(obtemGeneroPessoa(p->info), sizeof(char), MAX_TAM_GENERO, pFile);
}