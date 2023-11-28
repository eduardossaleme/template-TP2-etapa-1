#include "tSecretario.h"

struct tSecretario{
    tPessoa* info;
    char usuario[21];
    char senha[21];
    ACESSO acesso;
};

tSecretario* criaSecretario(tPessoa* infos, char* usuario, char* senha, ACESSO acesso){
    tSecretario* secretario = (tSecretario*)malloc(sizeof (tSecretario));
    secretario->info=infos;
    secretario->acesso=acesso;
    strcpy(secretario->usuario, usuario);
    strcpy(secretario->senha, senha);
    
    return secretario;
}

void desalocaSecretario(tSecretario* secretario){
    desalocaPessoa(secretario->info);
    free(secretario);
}