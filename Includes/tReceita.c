#include "tReceita.h"
#include "tMedico.h"

struct tReceita{
    char nomePaciente[MAX_TAM_NOME];
    eTipoUso tipoUso;
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    char intrucoes[MAX_TAM_INSTRUCOES];
    int qtd;
    char nomeMedico[MAX_TAM_NOME];
    char crm[MAX_TAM_CRM];
    char data[MAX_TAM_DATA];
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
    printf("NOME:%s\n", r->nomePaciente);
    printf("\nUSO %s\n", r->tipoUso);
    printf("\n%s\n", r->nomeMedicamento);
    printf("%d %s\n", r->qtd, r->tipoMedicamento);
    printf("\n%s\n", r->intrucoes);
    if(r->crm=="0" || r->crm==NULL){
        printf("\n ()\n");
    }
    else{
        printf("\n%s(%s)\n", r->nomeMedico, r->crm);
    }
    printf("%s\n", r->data);
}

void imprimeEmArquivoReceita(void *dado, char *path){
    if(dado==NULL) return;
    char nome[1030];
    tReceita* r = (tReceita*)dado;
    sprintf(nome, "%s/saida/receita.txt", path);
    FILE* pFile = fopen(nome, "w");
    fprintf(pFile, "RECEITUARIO\n");
    fprintf(pFile, "NOME:%s\n", r->nomePaciente);
    fprintf(pFile, "\nUSO %s\n", r->tipoUso);
    fprintf(pFile, "\n%s\n", r->nomeMedicamento);
    fprintf(pFile, "%d %s\n", r->qtd, r->tipoMedicamento);
    fprintf(pFile, "\n%s\n", r->intrucoes);
    if(r->crm=="0" || r->crm==NULL){
        fprintf(pFile, "\n ()\n");
    }
    else{
        fprintf(pFile, "\n%s(%s)\n", r->nomeMedico, r->crm);
    }
    fprintf(pFile, "%s\n", r->data);
    fclose(pFile);
}