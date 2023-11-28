#ifndef TSECRATARIO_H
#define TSECRETARIO_H

#include "tPessoa.h"

typedef struct tSecretario tSecretario;


tSecretario* criaSecretario(tPessoa* infos, char* usuario, char* senha, ACESSO acesso);

void desalocaSecretario(tSecretario* secretario);

#endif