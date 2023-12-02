#include "tSade.h"

struct tSade{
    tMedico** medicos;
    tPaciente** pacientes;
    tSecretario** secretarios;
    tConsulta** consultas;
    tPessoa* user;
    ACESSO nivelAcesso;
    int nMedicos, nPacientes, nSecretarios, nConsultas;
    char path[1000];
};

tSade* inicializaSade(){
    tSade* sade = (tSade*)calloc(1 ,sizeof(tSade));
    FILE* pFile;
    char arquivo[1020];
    sade->medicos=NULL;
    sade->secretarios=NULL;
    sade->pacientes=NULL;
    sade->consultas=NULL;
    printf("################################################\n DIGITE O CAMINHO DO BANCO DE DADOS:\n################################################\n");
    scanf("%s%*c", sade->path);
    sprintf(arquivo, "%s/secretarios.bin", sade->path);
    if(!(pFile = fopen(arquivo, "rb"))){
        cadastraSecretario(sade);
    }
    else{
        fclose(pFile);
        leBancoDeDadosSecretarios(sade);
        leBancoDeDadosPacientes(sade);
        leBancoDeDadosMedicos(sade);
    }

    return sade;
}

void leBancoDeDadosSecretarios(tSade* sade){
    char arquivo[1020];
    FILE* pFile;
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    char user[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    ACESSO acesso;
    tPessoa* info;

    sprintf(arquivo, "%s/secretarios.bin", sade->path);

    if((pFile = fopen(arquivo, "rb"))){
        fread(&sade->nSecretarios, sizeof(int), 1, pFile);
        
        sade->secretarios = (tSecretario**)realloc(sade->secretarios,(sade->nSecretarios)*sizeof(tSecretario*));

        for(int i=0;i<sade->nSecretarios;i++){
            fread(nome, sizeof(char), MAX_TAM_NOME, pFile);
            fread(cpf, sizeof(char), MAX_TAM_CPF, pFile);
            fread(data, sizeof(char), MAX_TAM_DATA, pFile);
            fread(telefone, sizeof(char), MAX_TAM_TELEFONE, pFile);
            fread(genero, sizeof(char), MAX_TAM_GENERO, pFile);
            fread(user, sizeof(char), MAX_TAM_LOGIN, pFile);
            fread(senha, sizeof(char), MAX_TAM_LOGIN, pFile);
            fread(&acesso, sizeof(ACESSO), 1, pFile);
            info = criaPessoa(nome, cpf, data, telefone, genero);
            sade->secretarios[i]=criaSecretario(info, user, senha, acesso);
        }
        fclose(pFile);
    }
}

void cadastraSecretario(tSade* sade){
    printf("#################### CADASTRO SECRETARIO #######################\n");
    printf("NOME COMPLETO: <inserir dado via teclado>\n");
    printf("CPF: <inserir dado via teclado>\n");
    printf("DATA DE NASCIMENTO: <inserir dado via teclado>\n");
    printf("TELEFONE: <inserir dado via teclado>\n");
    printf("GENERO: <inserir dado via teclado>\n");
    printf("NOME DE USUARIO: <inserir dado via teclado>\n");
    printf("SENHA: <inserir dado via teclado>\n");
    printf("NIVEL DE ACESSO: <inserir dado via teclado>\n");
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    char user[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char nivel[10];
    scanf("%s%*c", nome);
    scanf("%s%*c", cpf);
    scanf("%s%*c", data);
    scanf("%s%*c", telefone);
    scanf("%s%*c", genero);
    scanf("%s%*c", user);
    scanf("%s%*c", senha);
    scanf("%s%*c", nivel);
    ACESSO acesso;
    if(nivel=="USER"){
        acesso=USER;
    }
    else acesso = ADMIN;
    sade->secretarios = (tSecretario**)realloc(sade->secretarios,(1+sade->nSecretarios)*sizeof(tSecretario*));
    tPessoa* info = criaPessoa(nome, cpf, data, telefone, genero);
    sade->secretarios[sade->nSecretarios]=criaSecretario(info, user, senha, acesso);
    sade->nSecretarios++;
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("#################### CADASTRO SECRETARIO #######################\n");
    scanf("%*c");
}

void criaBancoDeDadosSecretarios(tSade* sade){
    char nome[1020];
    sprintf(nome, "%s/secretarios.bin", sade->path);
    FILE* pFile = fopen(nome, "wb");
    fwrite(&sade->nSecretarios, sizeof(int), 1, pFile);
    for(int i=0;i<sade->nSecretarios;i++){
        adicionaSecretarioBandoDeDados(sade->secretarios[i], pFile);
    }
    fclose(pFile);
}

void leBancoDeDadosPacientes(tSade* sade){
    char arquivo[1020];
    FILE* pFile;
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    tPessoa* info;

    sprintf(arquivo, "%s/pacientes.bin", sade->path);

    if((pFile = fopen(arquivo, "rb"))){
        fread(&sade->nPacientes, sizeof(int), 1, pFile);
        
        sade->pacientes = (tPaciente**)realloc(sade->pacientes,(sade->nPacientes)*sizeof(tPaciente*));

        for(int i=0;i<sade->nPacientes;i++){
            fread(nome, sizeof(char), MAX_TAM_NOME, pFile);
            fread(cpf, sizeof(char), MAX_TAM_CPF, pFile);
            fread(data, sizeof(char), MAX_TAM_DATA, pFile);
            fread(telefone, sizeof(char), MAX_TAM_TELEFONE, pFile);
            fread(genero, sizeof(char), MAX_TAM_GENERO, pFile);
            info = criaPessoa(nome, cpf, data, telefone, genero);
            sade->pacientes[i]=criaPaciente(info);
        }
        fclose(pFile);
    }
}

void cadastraPaciente(tSade* sade){
    printf("#################### CADASTRO PACIENTE #######################\n");
    printf("NOME COMPLETO: <inserir dado via teclado>\n");
    printf("CPF: <inserir dado via teclado>\n");
    printf("DATA DE NASCIMENTO: <inserir dado via teclado>\n");
    printf("TELEFONE: <inserir dado via teclado>\n");
    printf("GENERO: <inserir dado via teclado>\n");
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    scanf("%s%*c", nome);
    scanf("%s%*c", cpf);
    scanf("%s%*c", data);
    scanf("%s%*c", telefone);
    scanf("%s%*c", genero);
    ACESSO acesso;

    sade->pacientes = (tPaciente**)realloc(sade->pacientes,(1+sade->nPacientes)*sizeof(tPaciente*));
    tPessoa* info = criaPessoa(nome, cpf, data, telefone, genero);
    sade->pacientes[sade->nPacientes]=criaPaciente(info);
    sade->nPacientes++;
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("#################### CADASTRO PACIENTE #######################\n");
    scanf("%*c");
}

void criaBancoDeDadosPacientes(tSade* sade){
    char nome[1020];
    sprintf(nome, "%s/pacientes.bin", sade->path);
    FILE* pFile = fopen(nome, "wb");
    fwrite(&sade->nPacientes, sizeof(int), 1, pFile);
    for(int i=0;i<sade->nPacientes;i++){
        adicionaPacienteBandoDeDados(sade->pacientes[i], pFile);
    }
    fclose(pFile);
}

void leBancoDeDadosMedicos(tSade* sade){
    char arquivo[1020];
    FILE* pFile;
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    char user[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char crm[MAX_TAM_CRM];
    tPessoa* info;

    sprintf(arquivo, "%s/medicos.bin", sade->path);

    if((pFile = fopen(arquivo, "rb"))){
        fread(&sade->nMedicos, sizeof(int), 1, pFile);
        
        sade->medicos = (tMedico**)realloc(sade->medicos,(sade->nMedicos)*sizeof(tMedico*));

        for(int i=0;i<sade->nSecretarios;i++){
            fread(nome, sizeof(char), MAX_TAM_NOME, pFile);
            fread(cpf, sizeof(char), MAX_TAM_CPF, pFile);
            fread(data, sizeof(char), MAX_TAM_DATA, pFile);
            fread(telefone, sizeof(char), MAX_TAM_TELEFONE, pFile);
            fread(genero, sizeof(char), MAX_TAM_GENERO, pFile);
            fread(crm, sizeof(char), MAX_TAM_CRM, pFile);
            fread(user, sizeof(char), MAX_TAM_LOGIN, pFile);
            fread(senha, sizeof(char), MAX_TAM_LOGIN, pFile);
            info = criaPessoa(nome, cpf, data, telefone, genero);
            sade->medicos[i]=criaMedico(info, user, senha, crm);
        }
        fclose(pFile);
    }
}

void cadastraMedico(tSade* sade){
    printf("#################### CADASTRO SECRETARIO #######################\n");
    printf("NOME COMPLETO: <inserir dado via teclado>\n");
    printf("CPF: <inserir dado via teclado>\n");
    printf("DATA DE NASCIMENTO: <inserir dado via teclado>\n");
    printf("TELEFONE: <inserir dado via teclado>\n");
    printf("GENERO: <inserir dado via teclado>\n");
    printf("CRM: <inserir dado via teclado>\n");
    printf("NOME DE USUARIO: <inserir dado via teclado>\n");
    printf("SENHA: <inserir dado via teclado>\n");
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    char user[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char crm[MAX_TAM_CRM];
    scanf("%s%*c", nome);
    scanf("%s%*c", cpf);
    scanf("%s%*c", data);
    scanf("%s%*c", telefone);
    scanf("%s%*c", genero);
    scanf("%s%*c", crm);
    scanf("%s%*c", user);
    scanf("%s%*c", senha);
    ACESSO acesso;
    sade->medicos = (tMedico**)realloc(sade->medicos,(1+sade->nMedicos)*sizeof(tMedico*));
    tPessoa* info = criaPessoa(nome, cpf, data, telefone, genero);
    sade->medicos[sade->nMedicos]=criaMedico(info, user, senha, crm);
    sade->nMedicos++;
    printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
    printf("#################### CADASTRO SECRETARIO #######################\n");
    scanf("%*c");
}

void criaBancoDeDadosMedicos(tSade* sade){
    char nome[1020];
    sprintf(nome, "%s/medicos.bin", sade->path);
    FILE* pFile = fopen(nome, "wb");
    fwrite(&sade->nMedicos, sizeof(int), 1, pFile);
    for(int i=0;i<sade->nMedicos;i++){
        adicionaMedicoBandoDeDados(sade->medicos[i], pFile);
    }
    fclose(pFile);
}