#ifndef TSECRATARIO_H
#define TSECRETARIO_H

#include "tPessoa.h"

typedef struct tSecretario tSecretario;


tSecretario* criaSecretario(tPessoa* infos, char* usuario, char* senha, ACESSO acesso);

void desalocaSecretario(tSecretario* secretario);

tPessoa* obtemInfoSecretario(tSecretario* s);

char* obtemUsuarioSecretario(tSecretario* s);

char* obtemSenhaSecretario(tSecretario* s);

void adicionaSecretarioBandoDeDados(tSecretario* s, FILE* pFile);

#endif