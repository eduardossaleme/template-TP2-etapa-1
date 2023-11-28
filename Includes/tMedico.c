#include "tMedico.h"

struct tMedico{
    tPessoa* info;
    char usuario[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char crm[13];
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