#include "tEncaminhamento.h"

struct tEncaminhamento{
    char nomePaciente[MAX_TAM_NOME];
    char cpfPaciente[MAX_TAM_CPF];
    char nomeMedico[MAX_TAM_NOME];
    char crmMedico[MAX_TAM_CRM];
    char data[MAX_TAM_DATA];
    char motivo[MAX_TAM_MOTIVO];
    char especialidade[MAX_TAM_ESPECIALIDADE];
};

tEncaminhamento* criaEncaminhamento(char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* crmMedico, char* data, char* especialidade, char* motivo){
    tEncaminhamento* e=(tEncaminhamento*)calloc(1, sizeof(tEncaminhamento));
    strcpy(e->nomePaciente, nomePaciente);
    strcpy(e->cpfPaciente, cpfPaciente);
    strcpy(e->nomeMedico, nomeMedico);
    strcpy(e->crmMedico, crmMedico);
    strcpy(e->data, data);
    strcpy(e->motivo, motivo);
    strcpy(e->especialidade, especialidade);
    return e;
}

void imprimeNaTelaEncaminhamento(void* dado){
    if(dado==NULL) return;
    tEncaminhamento* e=(tEncaminhamento*)(dado);
    printf("PACIENTE: %s\n", e->nomePaciente);
    printf("CPF: %s\n\n", e->cpfPaciente);
    printf("ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    printf("MOTIVO: %s\n", e->motivo);
    printf("\n%s (%s)\n", e->nomeMedico, e->crmMedico);
    printf("%s\n\n", e->data);
}

void imprimeEmArquivoEncaminhamento(void* dado, char* path){
    if(dado==NULL) return;
    tEncaminhamento* e=(tEncaminhamento*)(dado);
    char nome[1030];
    sprintf(nome, "%s/encaminhamento.txt", path);
    FILE* pFile = fopen(nome, "a+");
    fprintf(pFile, "PACIENTE: %s\n", e->nomePaciente);
    fprintf(pFile, "CPF: %s\n\n", e->cpfPaciente);
    fprintf(pFile, "ESPECIALIDADE ENCAMINHADA: %s\n", e->especialidade);
    fprintf(pFile,"MOTIVO: %s\n", e->motivo);
    fprintf(pFile, "\n%s (%s)\n", e->nomeMedico, e->crmMedico);
    fprintf(pFile, "%s\n\n", e->data);
    fclose(pFile);
}

void desalocaEncaminhamento(void* dado){
    tEncaminhamento* e=(tEncaminhamento*)(dado);
    free(e);
}