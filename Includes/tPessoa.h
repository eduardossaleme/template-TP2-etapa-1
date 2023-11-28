#ifndef TPESSOA_H
#define TPESSOA_H

#define MAX_TAM_LOGIN 21
#define MAX_TAM_CPF 15
#define MAX_TAM_NOME 101
#define MAX_TAM_TELEFONE 15

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

#endif