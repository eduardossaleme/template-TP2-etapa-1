#include "tBiopsia.h"

struct tBiopsia{
    tLesao** lesoes;
    int nLesoes;
    char nomePaciente[MAX_TAM_NOME];
    char cpfPaciente[MAX_TAM_CPF];
    char nomeMedico[MAX_TAM_NOME];
    char crmMedico[MAX_TAM_CRM];
    char data[MAX_TAM_DATA];
};

tBiopsia* criaBiopsia(char* nomePaciente, char* cpfPaciente, char* nomeMedico, char* crmMedico, char* data){
    tBiopsia* b=(tBiopsia*)calloc(1, sizeof(tBiopsia));
    strcpy(b->nomePaciente, nomePaciente);
    strcpy(b->cpfPaciente, cpfPaciente);
    strcpy(b->nomeMedico, nomeMedico);
    strcpy(b->crmMedico, crmMedico);
    strcpy(b->data, data);
    b->lesoes=NULL;
    return b;
}

void adicionaLesaoBiopsia(tBiopsia* b, tLesao* l){
    b->lesoes=(tLesao**)realloc(b->lesoes, (1+b->nLesoes)*sizeof(tLesao*));
    b->lesoes[b->nLesoes]=l;
    b->nLesoes++;
}

void imprimeNaTelaBiopsia(void* dado){
    if(dado==NULL) return;
    tBiopsia* b=(tBiopsia*)(dado);
    printf("PACIENTE: %s\n", b->nomePaciente);
    printf("CPF: %s\n\n", b->cpfPaciente);
    printf("SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    for(int i=0; i<b->nLesoes;i++){
        printf("%s - %s - %s - %dMM\n", obtemRotuloLesao(b->lesoes[i]), obtemDiagnosticoLesao(b->lesoes[i]), obtemParteCorpoLesao(b->lesoes[i]), obtemTamanhoLesao(b->lesoes[i]));
    }
    printf("\n%s (%s)\n", b->nomeMedico, b->crmMedico);
    printf("%s\n\n", b->data);
}

void imprimeEmArquivoBiopsia(void* dado, char* path){
    if(dado==NULL) return;
    tBiopsia* b=(tBiopsia*)(dado);
    char nome[1030];
    sprintf(nome, "%s/biopsia.txt", path);
    FILE* pFile = fopen(nome, "a+");
    fprintf(pFile, "PACIENTE: %s\n", b->nomePaciente);
    fprintf(pFile, "CPF: %s\n\n", b->cpfPaciente);
    fprintf(pFile, "SOLICITACAO DE BIOPSIA PARA AS LESOES:\n");
    for(int i=0; i<b->nLesoes;i++){
        fprintf(pFile, "%s - %s - %s - %dMM\n", obtemRotuloLesao(b->lesoes[i]), obtemDiagnosticoLesao(b->lesoes[i]), obtemParteCorpoLesao(b->lesoes[i]), obtemTamanhoLesao(b->lesoes[i]));
    }
    fprintf(pFile, "\n%s (%s)\n", b->nomeMedico, b->crmMedico);
    fprintf(pFile, "%s\n\n", b->data);
    fclose(pFile);
}

void desalocaBiopsia(void* dado){
    tBiopsia* b=(tBiopsia*)(dado);
    free(b->lesoes);
    free(b);
}