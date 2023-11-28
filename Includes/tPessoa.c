#include "tPessoa.h"

struct tPessoa{
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[11];
    char telefone[MAX_TAM_TELEFONE];
    char genero[15];
};

tPessoa* criaPessoa(char* nome, char* cpf, char* data, char* telefone, char* genero){
    tPessoa* pessoa = (tPessoa*)malloc(sizeof(tPessoa));
    
    strcpy(pessoa->nome, nome);
    strcpy(pessoa->cpf, cpf);
    strcpy(pessoa->data, data);
    strcpy(pessoa->telefone, telefone);
    strcpy(pessoa->genero, genero);

    return pessoa;
}

void desalocaPessoa(tPessoa* pessoa){
    free(pessoa);
}