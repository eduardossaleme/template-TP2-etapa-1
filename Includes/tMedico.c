#include "tMedico.h"

struct tMedico{
    tPessoa* info;
    char usuario[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char crm[MAX_TAM_CRM];
};

tMedico* criaMedico(tPessoa* infos, char* usuario, char* senha, char* crm){
    tMedico* medico = (tMedico*)malloc(sizeof(tMedico));
    
    medico->info=infos;
    strcpy(medico->usuario, usuario);
    strcpy(medico->senha, senha);
    strcpy(medico->crm, crm);

    return medico;
}

void desalocaMedico(tMedico* medico){
    desalocaPessoa(medico->info);
    free(medico);
}

char* obtemCrmMedico(tMedico* m){
    return m->crm;
}

tPessoa* obtemInfoMedico(tMedico* m){
    return m->info;
}

char* obtemUsuarioMedico(tMedico* m){
    return m->usuario;
}

char* obtemSenhaMedico(tMedico* m){
    return m->senha;
}

void adicionaMedicoBandoDeDados(tMedico* m, FILE* pFile){
    fwrite(obtemNomePessoa(m->info), sizeof(char), MAX_TAM_NOME, pFile);
    fwrite(obtemCpfPessoa(m->info), sizeof(char), MAX_TAM_CPF, pFile);
    fwrite(obtemDataPessoa(m->info), sizeof(char), MAX_TAM_DATA, pFile);
    fwrite(obtemTelefonePessoa(m->info), sizeof(char), MAX_TAM_TELEFONE, pFile);
    fwrite(obtemGeneroPessoa(m->info), sizeof(char), MAX_TAM_GENERO, pFile);
    fwrite(m->crm, sizeof(char), MAX_TAM_CRM, pFile);
    fwrite(m->usuario, sizeof(char), MAX_TAM_LOGIN, pFile);
    fwrite(m->senha, sizeof(char), MAX_TAM_LOGIN, pFile);
}