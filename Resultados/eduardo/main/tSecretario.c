#include "tSecretario.h"

struct tSecretario{
    tPessoa* info;
    char usuario[21];
    char senha[21];
    ACESSO acesso;
};

tSecretario* criaSecretario(tPessoa* infos, char* usuario, char* senha, ACESSO acesso){
    tSecretario* secretario = (tSecretario*)calloc(1, sizeof (tSecretario));
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

tPessoa* obtemInfoSecretario(tSecretario* s){
    return s->info;
}

char* obtemUsuarioSecretario(tSecretario* s){
    return s->usuario;
}

char* obtemSenhaSecretario(tSecretario* s){
    return s->senha;
}

ACESSO obtemAcessoSecretario(tSecretario* s){
    return s->acesso;
}

void adicionaSecretarioBandoDeDados(tSecretario* s, FILE* pFile){
    escrecePessoaBinario(s->info, pFile);
    fwrite(s->usuario, sizeof(char), MAX_TAM_LOGIN, pFile);
    fwrite(s->senha, sizeof(char), MAX_TAM_LOGIN, pFile);
    fwrite(&s->acesso, sizeof(ACESSO), 1, pFile);
}