#ifndef TPESSOA_H
#define TPESSOA_H

#define MAX_TAM_LOGIN 21
#define MAX_TAM_CPF 15
#define MAX_TAM_NOME 101
#define MAX_TAM_TELEFONE 15
#define MAX_TAM_DATA 11
#define MAX_TAM_GENERO 15

typedef enum{
    MEDICO=0,
    USER=1,
    ADMIN=2
}ACESSO;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tPessoa tPessoa;

tPessoa* criaPessoa(char* nome, char* cpf, char* data, char* telefone, char* genero);

void desalocaPessoa(tPessoa* pessoa);

char* obtemNomePessoa(tPessoa* p);

char* obtemCpfPessoa(tPessoa* p);

char* obtemDataPessoa(tPessoa* p);

char* obtemTelefonePessoa(tPessoa* p);

char* obtemGeneroPessoa(tPessoa* p);

int calculaIdadePessoa(tPessoa* p, char* data);

void escrecePessoaBinario(tPessoa* p, FILE* f);

#endif