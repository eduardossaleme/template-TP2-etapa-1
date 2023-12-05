#include "tReceita.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct tReceita{
    char nomePaciente[100];
    eTipoUso tipoUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char intrucoes[MAX_TAM_INSTRUCOES];
    int qtd;
    char nomeMedico[100];
    char crm[13];
    char data[11];
};

tReceita *criaReceita(char *nomePaciente, eTipoUso tipoUso, char *nomeMedicamento,
                      char *tipoMedicamento, char *instrucoes, int qntd,
                      char *nomeMedico, char *CRM, char *dataStr){
    tReceita* r=(tReceita*)calloc(1, sizeof(tReceita));
    strcpy(r->nomePaciente,nomePaciente);
    strcpy(r->nomeMedicamento,nomeMedicamento);
    strcpy(r->tipoMedicamento, tipoMedicamento);
    strcpy(r->intrucoes, instrucoes);
    strcpy(r->nomeMedico, nomeMedico);
    strcpy(r->crm, CRM);
    strcpy(r->data, dataStr);
    r->tipoUso=tipoUso;
    r->qtd=qntd;
    return r;
}

void desalocaReceita(void *dado){
    if(dado==NULL) return;
    tReceita* r = (tReceita*)(dado);
    free(r);
}

void imprimeNaTelaReceita(void *dado){
    if(dado==NULL) return;
    tReceita* r = (tReceita*)(dado);
    printf("RECEITUARIO\n");
    printf("NOME: %s\n", r->nomePaciente);
    if(r->tipoUso == ORAL){
        printf("\nUSO ORAL\n");
    }
    else {
        printf("\nUSO TOPICO\n");
    }
    printf("\n%s\n", r->nomeMedicamento);
    printf("%d %s\n", r->qtd, r->tipoMedicamento);
    printf("\n%s\n\n", r->intrucoes);
    if(r->crm=="0" || r->crm==NULL){
        printf(" ()\n");
    }
    else{
        printf("%s (%s)\n", r->nomeMedico, r->crm);
    }
    printf("%s\n\n", r->data);
}

void imprimeEmArquivoReceita(void *dado, char *path) {
    if (dado == NULL) return;
    char nome[1030];
    tReceita* r = (tReceita*)dado;
    sprintf(nome, "%s/receita.txt", path);
    FILE* pFile = fopen(nome, "a+");
    if (pFile == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fprintf(pFile, "RECEITUARIO\n");
    fprintf(pFile, "NOME: %s\n", r->nomePaciente);
    if(r->tipoUso == ORAL){
        fprintf(pFile, "\nUSO ORAL\n");
    }
    else {
        fprintf(pFile, "\nUSO TOPICO\n");
    }
    fprintf(pFile, "\n%s\n", r->nomeMedicamento);
    fprintf(pFile, "%d %s\n", r->qtd, r->tipoMedicamento);
    fprintf(pFile, "\n%s\n\n", r->intrucoes);

    // Corrigir a condição para verificar se a string é nula ou vazia
    if (r->crm == NULL || strcmp(r->crm, "0") == 0) {
        fprintf(pFile, " ()\n");
    } else {
        fprintf(pFile, "%s (%s)\n", r->nomeMedico, r->crm);
    }

    fprintf(pFile, "%s\n\n", r->data);
    fclose(pFile);
}