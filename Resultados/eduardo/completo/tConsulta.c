#include "tConsulta.h"

struct tConsulta{
    char data[MAX_TAM_DATA];
    char crmMedico[MAX_TAM_CRM];
    int nLesoes, id, diabetes, fumante, alergia, cancer;
    char tipoPele[3];
    int *idLesao;
};

tConsulta* criaConsulta(char* data, int diabetes, int fumante, int alergia, int cancer, char* tipoPele, char* crm, int id){
    tConsulta* consulta=(tConsulta*)calloc(1, sizeof(tConsulta));
    strcpy(consulta->data, data);
    consulta->diabetes=diabetes;
    consulta->fumante=fumante;
    consulta->alergia=alergia;
    consulta->cancer=cancer;
    strcpy(consulta->tipoPele, tipoPele);
    strcpy(consulta->crmMedico, crm);
    consulta->idLesao=NULL;
    consulta->id=id;
    return consulta;
}

void adcionaLesaoConsulta(tConsulta* c, int id){
    c->idLesao=(int*)realloc(c->idLesao, (c->nLesoes+1)*sizeof(int));
    c->idLesao[c->nLesoes]=id;
    c->nLesoes++;
}

void adicionaConsultaBandoDeDados(tConsulta* c, FILE* pFile){
    fwrite(c->data, sizeof(char), MAX_TAM_DATA, pFile);
    fwrite(&c->diabetes, sizeof(int), 1, pFile);
    fwrite(&c->fumante, sizeof(int), 1, pFile);
    fwrite(&c->alergia, sizeof(int), 1, pFile);
    fwrite(&c->cancer, sizeof(int), 1, pFile);
    fwrite(c->tipoPele, sizeof(char), 3, pFile);
    fwrite(c->crmMedico, sizeof(char), MAX_TAM_CRM, pFile);
    fwrite(&c->id, sizeof(int), 1, pFile);
    fwrite(&c->nLesoes, sizeof(int), 1, pFile);
    for(int i=0;i<c->nLesoes;i++){
        fwrite(&c->idLesao[i], sizeof(int), 1, pFile);
    }
}

void desalocaConsulta(tConsulta* c){
    free(c->idLesao);
    free(c);
}

char* obtemDataConsulta(tConsulta* c){
    return c->data;
}

char* obtemCrmConsulta(tConsulta* c){
    return c->crmMedico;
}

char* obtemTipoPeleConsulta(tConsulta* c){
    return c->tipoPele;
}

int obtemIdLesaoConsulta(tConsulta* c, int i){
    return c->idLesao[i];
}

int obtemNLesoesConsulta(tConsulta* c){
    return c->nLesoes;
}