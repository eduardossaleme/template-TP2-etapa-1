#include "tPessoa.h"

struct tPessoa{
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
};

tPessoa* criaPessoa(char* nome, char* cpf, char* data, char* telefone, char* genero){
    tPessoa* pessoa = (tPessoa*)malloc(sizeof(tPessoa));
    
    strcpy(pessoa->nome, nome);
    strcpy(pessoa->cpf, cpf);
    strcpy(pessoa->data, data);
    strcpy(pessoa->telefone, telefone);
    strcpy(pessoa->genero, genero);
    // printf("nome %s\n", pessoa->nome);
    // printf("cpf %s\n", pessoa->cpf);
    // printf("data %s\n", pessoa->data);
    // printf("tel %s\n", pessoa->telefone);
    // printf("gen %s\n", pessoa->genero);

    return pessoa;
}

void desalocaPessoa(tPessoa* pessoa){
    free(pessoa);
}

char* obtemNomePessoa(tPessoa* p){
    return p->nome;
}

char* obtemCpfPessoa(tPessoa* p){
    return p->cpf;
}

char* obtemDataPessoa(tPessoa* p){
    return p->data;
}

char* obtemTelefonePessoa(tPessoa* p){
    return p->telefone;
}

char* obtemGeneroPessoa(tPessoa* p){
    return p->genero;
}