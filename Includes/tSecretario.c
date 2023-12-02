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

    // printf("user %s\n", secretario->usuario);
    // printf("senha %s\n", secretario->senha);
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

void adicionaSecretarioBandoDeDados(tSecretario* s, FILE* pFile){
    fwrite(obtemNomePessoa(s->info), sizeof(char), MAX_TAM_NOME, pFile);
    fwrite(obtemCpfPessoa(s->info), sizeof(char), MAX_TAM_CPF, pFile);
    fwrite(obtemDataPessoa(s->info), sizeof(char), MAX_TAM_DATA, pFile);
    fwrite(obtemTelefonePessoa(s->info), sizeof(char), MAX_TAM_TELEFONE, pFile);
    fwrite(obtemGeneroPessoa(s->info), sizeof(char), MAX_TAM_GENERO, pFile);
    fwrite(s->usuario, sizeof(char), MAX_TAM_LOGIN, pFile);
    fwrite(s->senha, sizeof(char), MAX_TAM_LOGIN, pFile);
    fwrite(&s->acesso, sizeof(ACESSO), 1, pFile);
}