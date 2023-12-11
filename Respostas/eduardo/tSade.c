#include "tSade.h"

struct tSade{
    tMedico** medicos;
    tPaciente** pacientes;
    tSecretario** secretarios;
    tConsulta** consultas;
    tLesao** lesoes;
    tPessoa* user;
    ACESSO nivelAcesso;
    int nMedicos, nPacientes, nSecretarios, nConsultas, nLesoes;
    char crm[MAX_TAM_CRM];
    char nomeMedico[MAX_TAM_NOME];
    char caminhoDB[1000];
    char path[980];
    char data[MAX_TAM_DATA];
    tFila* fila;
};

tSade* inicializaSade(char* path){
    tSade* sade = (tSade*)calloc(1 ,sizeof(tSade));
    FILE* pFile;
    char arquivo[1020];
    char caminhoDB[300];
    sade->medicos=NULL;
    sade->secretarios=NULL;
    sade->pacientes=NULL;
    sade->consultas=NULL;
    sade->lesoes=NULL;
    sade->fila=criaFila();
    strcpy(sade->data, "31/12/2023");
    printf("################################################\n DIGITE O CAMINHO DO BANCO DE DADOS:\n################################################\n");
    scanf("%s%*c",caminhoDB);
    sprintf(sade->caminhoDB, "%s/%s", path, caminhoDB);
    sprintf(sade->path, "%s/saida", path);
    sprintf(arquivo, "%s/secretarios.bin", sade->caminhoDB);
    printf("Caminho do banco de dados: %s\n", sade->caminhoDB);
    printf("Caminho da pasta de saida: %s\n", sade->path);
    if(!(pFile = fopen(arquivo, "rb"))){
        cadastraSecretario(sade);
    }
    else{
        fclose(pFile);
        leBancoDeDadosSecretarios(sade);
        leBancoDeDadosPacientes(sade);
        leBancoDeDadosMedicos(sade);
        leBancoDeDadosConsulta(sade);
        leBancoDeDadosLesoes(sade);
    }
    realizaLogin(sade);
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

    sprintf(arquivo, "%s/secretarios.bin", sade->caminhoDB);

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
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    char user[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char nivel[10];
    printf("#################### CADASTRO SECRETARIO #######################\n");
    printf("NOME COMPLETO: ");
    scanf("%[^\n]%*c", nome);
    printf("CPF: ");
    scanf("%s%*c", cpf);
    printf("DATA DE NASCIMENTO: ");
    scanf("%s%*c", data);
    printf("TELEFONE: ");
    scanf("%s%*c", telefone);
    printf("GENERO: ");
    scanf("%s%*c", genero);
    printf("NOME DE USUARIO: ");
    scanf("%[^\n]%*c", user);
    printf("SENHA: ");
    scanf("%[^\n]%*c", senha);
    printf("NIVEL DE ACESSO: ");
    scanf("%s%*c", nivel);
    
    ACESSO acesso;
    if((strcmp("ADMIN", nivel))){
        acesso=USER;
    }
    else acesso = ADMIN;
    if(cpfJaExistente(sade, cpf)){
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
    }
    else{
        sade->secretarios = (tSecretario**)realloc(sade->secretarios,(1+sade->nSecretarios)*sizeof(tSecretario*));
    tPessoa* info = criaPessoa(nome, cpf, data, telefone, genero);
    sade->secretarios[sade->nSecretarios]=criaSecretario(info, user, senha, acesso);
    sade->nSecretarios++;
    if(sade->nSecretarios>1){
        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("#################### CADASTRO SECRETARIO #######################\n");
        scanf("%*c%*c");
    }
    }
}

void criaBancoDeDadosSecretarios(tSade* sade){
    char nome[1020];
    int i;
    sprintf(nome, "%s/secretarios.bin", sade->caminhoDB);
    FILE *arquivo;
    arquivo = fopen(nome, "wb");
    if(arquivo==NULL){
        printf("%s\n", sade->caminhoDB);
        printf("ERRO\n");
        return;
    }
    fwrite(&sade->nSecretarios, sizeof(int), 1, arquivo);
    
    for(i=0;i<sade->nSecretarios;i++){
        adicionaSecretarioBandoDeDados(sade->secretarios[i], arquivo);
    }
    fclose(arquivo);
}

void leBancoDeDadosPacientes(tSade* sade){
    char arquivo[1020];
    FILE* pFile;
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    int nConsultas, id;
    tPessoa* info;

    sprintf(arquivo, "%s/pacientes.bin", sade->caminhoDB);

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
            fread(&nConsultas, sizeof(int), 1, pFile);
            for(int j=0; j<nConsultas;j++){
                fread(&id, sizeof(int), 1, pFile);
                adicionaConsultaPaciente(sade->pacientes[i], id);
            }
        }
        fclose(pFile);
    }
}

void cadastraPaciente(tSade* sade){
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    
    printf("#################### CADASTRO PACIENTE #######################\n");
    printf("NOME COMPLETO: ");
    scanf("%[^\n]%*c", nome);
    printf("CPF: ");
    scanf("%s%*c", cpf);
    printf("DATA DE NASCIMENTO: ");
    scanf("%s%*c", data);
    printf("TELEFONE: ");
    scanf("%s%*c", telefone);
    printf("GENERO: ");
    scanf("%s%*c", genero);
    
    if(cpfJaExistente(sade, cpf)){
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
    }
    else{
        sade->pacientes = (tPaciente**)realloc(sade->pacientes,(1+sade->nPacientes)*sizeof(tPaciente*));
        tPessoa* info = criaPessoa(nome, cpf, data, telefone, genero);
        sade->pacientes[sade->nPacientes]=criaPaciente(info);
        sade->nPacientes++;
        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("#################### CADASTRO PACIENTE #######################\n");
        scanf("%*c%*c");
    }
}

void criaBancoDeDadosPacientes(tSade* sade){
    if(sade->nPacientes==0) return;
    char nome[1020];
    sprintf(nome, "%s/pacientes.bin", sade->caminhoDB);
    FILE* arquivo;
    arquivo = fopen(nome, "wb");
    if(arquivo==NULL){
        printf("%s\n", sade->caminhoDB);
        printf("ERRO\n");
        return;
    }
    fwrite(&sade->nPacientes, sizeof(int), 1, arquivo);
    for(int i=0;i<sade->nPacientes;i++){
        adicionaPacienteBandoDeDados(sade->pacientes[i], arquivo);
    }
    fclose(arquivo);
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

    sprintf(arquivo, "%s/medicos.bin", sade->caminhoDB);

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
    char nome[MAX_TAM_NOME];
    char cpf[MAX_TAM_CPF];
    char data[MAX_TAM_DATA];
    char telefone[MAX_TAM_TELEFONE];
    char genero[MAX_TAM_GENERO];
    char user[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char crm[MAX_TAM_CRM];
    printf("#################### CADASTRO MEDICO #######################\n");
    printf("NOME COMPLETO: ");
    scanf("%[^\n]%*c", nome);
    printf("CPF: ");
    scanf("%s%*c", cpf);
    printf("DATA DE NASCIMENTO: ");
    scanf("%s%*c", data);
    printf("TELEFONE: ");
    scanf("%s%*c", telefone);
    printf("GENERO: ");
    scanf("%s%*c", genero);
    printf("CRM: ");
    scanf("%s%*c", crm);
    printf("NOME DE USUARIO: ");
    scanf("%s%*c", user);
    printf("SENHA: ");
    scanf("%s%*c", senha);

     if(cpfJaExistente(sade, cpf)){
        printf("CPF JA EXISTENTE. OPERACAO NAO PERMITIDA.\n");
    }
    else{
        sade->medicos = (tMedico**)realloc(sade->medicos,(1+sade->nMedicos)*sizeof(tMedico*));
        tPessoa* info = criaPessoa(nome, cpf, data, telefone, genero);
        sade->medicos[sade->nMedicos]=criaMedico(info, user, senha, crm);
        sade->nMedicos++;
        printf("CADASTRO REALIZADO COM SUCESSO. PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU INICIAL\n");
        printf("#################### CADASTRO MEDICO #######################\n");
        scanf("%*c%*c");
    }
    
}

void criaBancoDeDadosMedicos(tSade* sade){
    if(sade->nMedicos==0) return;
    char nome[1020];
    sprintf(nome, "%s/medicos.bin", sade->caminhoDB);
    FILE* pFile = fopen(nome, "wb");
    fwrite(&sade->nMedicos, sizeof(int), 1, pFile);
    for(int i=0;i<sade->nMedicos;i++){
        adicionaMedicoBandoDeDados(sade->medicos[i], pFile);
    }
    fclose(pFile);
}

void leBancoDeDadosConsulta(tSade* sade){
    char arquivo[1020];
    FILE* pFile;
    char data[MAX_TAM_DATA];
    char tipoPele[3];
    char crmMedico[MAX_TAM_CRM];
    int diabetes, fumante, alergia, cancer, id, nLesoes, idLesao,j;

    sprintf(arquivo, "%s/consultas.bin", sade->caminhoDB);

    if((pFile = fopen(arquivo, "rb"))){
        fread(&sade->nConsultas, sizeof(int), 1, pFile);
        
        sade->consultas = (tConsulta**)realloc(sade->consultas,(sade->nConsultas)*sizeof(tConsulta*));

        for(int i=0;i<sade->nConsultas;i++){
            fread(data, sizeof(char), MAX_TAM_DATA, pFile);
            fread(&diabetes, sizeof(int), 1, pFile);
            fread(&fumante, sizeof(int), 1, pFile);
            fread(&alergia, sizeof(int), 1, pFile);
            fread(&cancer, sizeof(int), 1, pFile);
            fread(tipoPele, sizeof(char), 3, pFile);
            fread(crmMedico, sizeof(char), MAX_TAM_CRM, pFile);
            fread(&id, sizeof(int), 1, pFile);
            sade->consultas[i]=criaConsulta(data, diabetes, fumante, alergia, cancer, tipoPele, crmMedico, id);
            fread(&nLesoes, sizeof(int), 1, pFile);
            for(j=0;j<nLesoes;j++){
                fread(&idLesao, sizeof(int), 1, pFile);
                adcionaLesaoConsulta(sade->consultas[i], idLesao);
            }
        }
        fclose(pFile);
    }
}

void criaBancoDeDadosConsulta(tSade* sade){
    if(sade->nConsultas==0) return;
    char nome[1020];
    sprintf(nome, "%s/consultas.bin", sade->caminhoDB);
    FILE* pFile = fopen(nome, "wb");
    fwrite(&sade->nConsultas, sizeof(int), 1, pFile);
    for(int i=0;i<sade->nConsultas;i++){
        adicionaConsultaBandoDeDados(sade->consultas[i], pFile);
    }
    fclose(pFile);
}

void leBancoDeDadosLesoes(tSade* sade){
    char arquivo[1020];
    FILE* pFile;

    sprintf(arquivo, "%s/lesoes.bin", sade->caminhoDB);

    if((pFile = fopen(arquivo, "rb"))){
        fread(&sade->nLesoes, sizeof(int), 1, pFile);
        
        sade->lesoes = (tLesao**)realloc(sade->lesoes,(sade->nLesoes)*sizeof(tLesao*));

        for(int i=0;i<sade->nLesoes;i++){

            sade->lesoes[i]=leLesaoBancoDeDados(pFile);
        }
        fclose(pFile);
    }
}

void criaBancoDeDadosLesoes(tSade* sade){
    if(sade->nLesoes==0) return;
    char nome[1020];
    sprintf(nome, "%s/lesoes.bin", sade->caminhoDB);
    FILE* pFile = fopen(nome, "wb");
    fwrite(&sade->nLesoes, sizeof(int), 1, pFile);
    for(int i=0;i<sade->nLesoes;i++){
        adcionaLesaoBancoDeDados(sade->lesoes[i], pFile);
    }
    fclose(pFile);
}

void realizaLogin(tSade* sade){
    char user[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    int i, aux2, aux1=1;
    while(1){
        printf("######################## ACESSO MINI-SADE ######################\n");
        printf("DIGITE SEU LOGIN: ");
        scanf("%s%*c", user);
        printf("DIGITE SUA SENHA: ");
        scanf("%s%*c", senha);
        printf("###############################################################\n");
        aux2=1;
        for(i=0; i<sade->nSecretarios;i++){
            if(!(strcmp(user, obtemUsuarioSecretario(sade->secretarios[i])))){
                if(!(strcmp(senha, obtemSenhaSecretario(sade->secretarios[i])))){
                    aux1=0;
                    sade->nivelAcesso=obtemAcessoSecretario(sade->secretarios[i]);
                    sade->user=obtemInfoSecretario(sade->secretarios[i]);
                    strcpy(sade->crm, "");
                    strcpy(sade->nomeMedico, "");
                    break;
                }
                else{
                    aux2=0;
                }
            }
        }
        for(i=0;i<sade->nMedicos;i++){
            if(!(strcmp(user, obtemUsuarioMedico(sade->medicos[i])))){
                if(!(strcmp(senha, obtemSenhaMedico(sade->medicos[i])))){
                    aux1=0;
                    sade->nivelAcesso=MEDICO;
                    sade->user=obtemInfoMedico(sade->medicos[i]);
                    strcpy(sade->crm,obtemCrmMedico(sade->medicos[i]));
                    strcpy(sade->nomeMedico,obtemNomePessoa(obtemInfoMedico(sade->medicos[i])));
                    break;
                }
                else{
                    aux2=0;
                }
            }
        }
        if(aux1==0) break;
        if(aux2==0) printf("SENHA INCORRETA\n");
        else printf("USUARIO INEXISTENTE\n"); 
    }  
}

void desalocaSade(tSade* sade){
    int i;
    for(i=0;i<sade->nMedicos;i++){
        desalocaMedico(sade->medicos[i]);
    }
    if(sade->medicos!=NULL) free(sade->medicos);
    for(i=0;i<sade->nPacientes;i++){
        desalocaPaciente(sade->pacientes[i]);
    }
    if(sade->pacientes!=NULL) free(sade->pacientes);
    for(i=0;i<sade->nSecretarios;i++){
        desalocaSecretario(sade->secretarios[i]);
    }
    if(sade->secretarios!=NULL) free(sade->secretarios);
    for(i=0;i<sade->nConsultas;i++){
        desalocaConsulta(sade->consultas[i]);
    }
    if(sade->consultas!=NULL) free(sade->consultas);
    for(i=0;i<sade->nLesoes;i++){
        desalocaLesao(sade->lesoes[i]);
    }
    if(sade->lesoes!=NULL) free(sade->lesoes);
    desalocaFila(sade->fila);
    free(sade);
}

void menuSade(tSade* sade){
    char opcao;
    while(1){
        printf("####################### MENU PRINCIPAL #########################\n");
                                        printf("ESCOLHA UMA OPCAO:\n");
        if(sade->nivelAcesso == ADMIN)  printf("(1) CADASTRAR SECREATRIO\n");
        if(sade->nivelAcesso != MEDICO) printf("(2) CADASTRAR MEDICO\n");
        if(sade->nivelAcesso != MEDICO) printf("(3) CADASTRAR PACIENTE\n");
        if(sade->nivelAcesso != USER)   printf("(4) REALIZAR CONSULTA\n");
                                        printf("(5) BUSCAR PACIENTE\n");
                                        printf("(6) RELATORIO GERAL\n");
                                        printf("(7) FILA DE IMPRESSAO\n");
                                        printf("(8) FINALIZAR O PROGRAMA\n");
                                        printf("###############################################################\n");
        scanf("%c%*c", &opcao);
        if(opcao=='1' && sade->nivelAcesso==ADMIN){
            cadastraSecretario(sade);
        }
        else if (opcao=='2' && sade->nivelAcesso!=MEDICO){
            cadastraMedico(sade);
        }
        else if (opcao=='3' && sade->nivelAcesso!=MEDICO){
            cadastraPaciente(sade);
        }
        else if (opcao=='4' && sade->nivelAcesso!=USER){
            iniciaConsulta(sade);
        }
        else if (opcao=='5'){
            buscaPaciente(sade);
        }
        else if (opcao=='6'){
            geraRelatorioGeral(sade);
        }
        else if (opcao=='7'){
            filaDeImpressao(sade);
        }
        else if (opcao=='8'){
            break;
        }
    }
}

void criaBancoDeDados(tSade* sade){
    criaBancoDeDadosMedicos(sade);
    criaBancoDeDadosPacientes(sade);
    criaBancoDeDadosSecretarios(sade);
    criaBancoDeDadosConsulta(sade);
    criaBancoDeDadosLesoes(sade);
}

void filaDeImpressao(tSade* sade){
    char c;
    while(1){
        printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
        printf("ESCOLHA UMA OPCAO:\n(1)EXECUTAR FILA DE IMPRESSAO\n(2)RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        scanf("%c%*c", &c);
        if(c=='1'){
            printf("################### FILA DE IMPRESSAO MEDICA #####################\n");
            printf("EXECUTANDO FILA DE IMPRESSÃO:\n");
            imprimeFila(sade->fila, sade->path);
            printf("PRESSIONE QUALQUER TECLA PARA VOLTAR PARA O MENU PRINCIPAL\n");
            printf("###########################################################\n");
            scanf("%*c%*c");
        }
        else if(c=='2'){
            break;
        }
    }
}

void buscaPaciente(tSade* sade){
    int aux=0;
    char c;
    char nome[MAX_TAM_NOME];
    printf("#################### BUSCAR PACIENTES #######################\n");
    printf("NOME DO PACIENTE: ");
    scanf("%[^\n]%*c", nome);
    printf("############################################################\n");
    tListaBusca* lista = criaListaBusca();
    for(int i=0;i<sade->nPacientes;i++){
        if(!(strcmp(nome, obtemNomePessoa(obtemInfoPaciente(sade->pacientes[i]))))){
            adicionaListaBusca(lista, obtemInfoPaciente(sade->pacientes[i]));
            aux=1;
        }
    }
    if(aux==0){
        printf("#################### BUSCAR PACIENTES #######################\n");
        printf("NENHUM PACIENTE FOI ENCONTRADO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        desalocaListaBusca(lista);
    }
    else{
        printf("#################### BUSCAR PACIENTES #######################\n");
        printf("PACIENTES ENCONTRADOS:\n");
        imprimeTelaListaBusca(lista);
        while (1)
        {
            printf("SELECIONE UMA OPCAO:\n");
            printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
            printf("(2) RETORNAR AO MENU PRINCIPAL\n");
            printf("############################################################\n");
            scanf("%c%*c", &c);
            if(c=='1'){
                insereDocumentoFila(sade->fila, lista, imprimeTelaListaBusca, imprimeArquivoListaBusca, desalocaListaBusca);
                printf("#################### BUSCAR PACIENTES #######################\n");
                printf("LISTA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU PRINCIPAL\n");
                printf("############################################################\n");
                scanf("%*c%*c");
                break;
            }
            if(c=='2'){
                desalocaListaBusca(lista);
                break;
            }
        }  
    }

}

int cpfJaExistente(tSade* sade, char* cpf){
    int i, aux=0;
    for(i=0;i<sade->nPacientes;i++){
        if(!(strcmp(cpf, obtemCpfPessoa(obtemInfoPaciente(sade->pacientes[i]))))){
            aux=1;
        }
    }
    for(i=0;i<sade->nSecretarios;i++){
        if(!(strcmp(cpf, obtemCpfPessoa(obtemInfoSecretario(sade->secretarios[i]))))){
            aux=1;
        }
    }
    for(i=0;i<sade->nMedicos;i++){
        if(!(strcmp(cpf, obtemCpfPessoa(obtemInfoMedico(sade->medicos[i]))))){
            aux=1;
        }
    }
    return aux;
}

void iniciaConsulta(tSade* sade){
    tPaciente* paciente;
    char cpf[MAX_TAM_CPF];
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CPF DO PACIENTE: ");
    scanf("%s%*c", cpf);
    printf("############################################################\n");
    int i, aux=0;
    for(i=0;i<sade->nPacientes;i++){
        if(!(strcmp(cpf, obtemCpfPessoa(obtemInfoPaciente(sade->pacientes[i]))))){
            paciente=sade->pacientes[i];
            aux=1;
        }
    }
    if(aux==0){
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("CPF DO PACIENTE: %s\n", cpf);
        printf("PACIENTE SEM CADASTRO\n\n");
        printf("PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
        printf("############################################################\n");
        scanf("%*c%*c");
        return;
    }
    else{
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("CPF DO PACIENTE: %s\n", cpf);
        printf("- - -\n");
        printf("- NOME: %s\n", obtemNomePessoa(obtemInfoPaciente(paciente)));
        printf("- DATA DE NASCIMENTO: %s\n", obtemDataPessoa(obtemInfoPaciente(paciente)));
        printf("- - -\n\n");
        realizaConsulta(sade, paciente);
        adicionaConsultaPaciente(paciente, sade->nConsultas);
    }
}

void realizaConsulta(tSade* sade, tPaciente* paciente){
    char data[MAX_TAM_DATA];
    char tipoPele[3];
    int diabetes, fumante, alergia, cancer, n=0, aux, dia, mes, ano;
    char opcao;
    printf("DATA DA CONSULTA: ");
    scanf("%d/%d/%d\n", &dia, &mes, &ano);
    printf("POSSUI DIABETES: ");
    scanf("%d%*c", &diabetes);
    printf("FUMANTE:");
    scanf("%d%*c", &fumante);
    printf("ALEGIA A MEDICAMENTO: ");
    scanf("%d%*c", &alergia);
    printf("HISTORICO DE CANCER: ");
    scanf("%d%*c", &cancer);
    printf("TIPO DE PELE: ");
    scanf("%s%*c", tipoPele);
    printf("############################################################\n");
    sprintf(data, "%d/%d/%d", dia, mes, ano);
    sade->consultas=(tConsulta**)realloc(sade->consultas, (sade->nConsultas+1)*sizeof(tConsulta*));
    sade->consultas[sade->nConsultas]=criaConsulta(data, diabetes, fumante, alergia, cancer, tipoPele, sade->crm, sade->nConsultas);
    while(1){
        printf("#################### CONSULTA MEDICA #######################\n");
        printf("ESCOLHA UMA OPCAO:\n");
        printf("(1) CADASTRAR LESAO\n");
        printf("(2) GERAR RECEITA MEDICA\n");
        printf("(3) SOLICITACAO DE BIOPSIA\n");
        printf("(4) ENCAMINHAMENTO\n");
        printf("(5) ENCERRAR CONSULTA\n");
        printf("############################################################\n");
        aux=1;
        scanf("%c%*c", &opcao);
        if(opcao=='1'){
            n++;
            cadastraLesao(sade, n);
        }
        else if (opcao=='2'){
            geraReceita(sade, paciente, data);
        }
        else if (opcao=='3'){
            for(int i=0;i<obtemNLesoesConsulta(sade->consultas[sade->nConsultas]);i++){
                aux = aux + necessitaCirurgiaLesao(sade->lesoes[obtemIdLesaoConsulta(sade->consultas[sade->nConsultas], i)]);
            }
            if(aux==0){
                printf("#################### CONSULTA MEDICA #######################\n");
                printf("NAO E POSSIVEL SOLICITAR BIOPSIA SEM LESAO CIRURGICA. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
                printf("############################################################\n");
                scanf("%*c%*c");
            }
            else{
                geraBiopsia(sade, paciente, data);
            }
        }
        else if (opcao=='4'){
            geraEncaminhamento(sade, paciente, data);
        }
        else if (opcao=='5'){
            break;
        }
    }
    sade->nConsultas++;
}

void cadastraLesao(tSade* sade, int n){
    char diagnostico[MAX_TAM_DIAGNOSTICO];
    char parteCorpo[MAX_TAM_PCH];
    int tamanho, cirurgia, crioterapia;
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("CADASTRO DE LESAO:\n");
    printf("DIAGNOSTICO CLINICO: ");
    scanf("%[^\n]%*c", diagnostico);
    printf("REGIAO DO CORPO: ");
    scanf("%[^\n]%*c",parteCorpo);
    printf("TAMANHO: ");
    scanf("%d%*c", &tamanho);
    printf("ENVIAR PARA CIRURGIA: ");
    scanf("%d%*c", &cirurgia);
    printf("ENVIAR PARA CRIOTERAPIA: ");
    scanf("%d%*c", &crioterapia);
    sade->lesoes=(tLesao**)realloc(sade->lesoes, (sade->nLesoes+1)*sizeof(tLesao*));
    sade->lesoes[sade->nLesoes]=criaLesao(diagnostico, parteCorpo, tamanho, cirurgia, crioterapia, sade->nLesoes, n);
    adcionaLesaoConsulta(sade->consultas[sade->nConsultas], sade->nLesoes);
    sade->nLesoes++;
    printf("LESAO REGISTRADA COM SUCESSO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c%*c");
}

void geraReceita(tSade* sade, tPaciente* p, char* data){
    printf("#################### CONSULTA MEDICA #######################\n");
    char tipoUso[9];
    char nomeMedicamento[MAX_TAM_NOME_MEDICAMENTO];
    char tipoMedicamento[MAX_TAM_TIPO_MEDICAMENTO];
    int qtd;
    char instrucoes[MAX_TAM_INSTRUCOES];
    tReceita* r;
    printf("RECEITA MEDICA:\n");
    printf("TIPO DE USO: ");
    scanf("%s%*c", tipoUso);
    printf("NOME DO MEDICAMENTO: ");
    scanf("%[^\n]%*c", nomeMedicamento);
    printf("TIPO DE MEDICAMENTO: ");
    scanf("%[^\n]%*c", tipoMedicamento);
    printf("QUANTIDADE: ");
    scanf("%d%*c", &qtd);
    printf("INSTRUÇÕES DE USO: ");
    scanf("%[^\n]%*c", instrucoes);
    if(sade->nivelAcesso==MEDICO){
        if(!strcmp(tipoUso, "ORAL")){
            r = criaReceita(obtemNomePessoa(obtemInfoPaciente(p)), ORAL, nomeMedicamento, tipoMedicamento, instrucoes, qtd, obtemNomePessoa(sade->user), sade->crm,data);
        }
        else{
            r = criaReceita(obtemNomePessoa(obtemInfoPaciente(p)), TOPICO, nomeMedicamento, tipoMedicamento, instrucoes, qtd, obtemNomePessoa(sade->user), sade->crm,data);
        }
    }
    else{
        if(!strcmp(tipoUso, "ORAL")){
            r = criaReceita(obtemNomePessoa(obtemInfoPaciente(p)), ORAL, nomeMedicamento, tipoMedicamento, instrucoes, qtd, "", sade->crm,data);
        }
        else{
            r = criaReceita(obtemNomePessoa(obtemInfoPaciente(p)), TOPICO, nomeMedicamento, tipoMedicamento, instrucoes, qtd, "", sade->crm,data);
        }
    }
    insereDocumentoFila(sade->fila, r, imprimeNaTelaReceita, imprimeEmArquivoReceita, desalocaReceita);
    printf("RECEITA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c%*c");
}

void geraBiopsia(tSade* sade, tPaciente* p, char* data){
    tBiopsia* b=criaBiopsia(obtemNomePessoa(obtemInfoPaciente(p)), obtemCpfPessoa(obtemInfoPaciente(p)), sade->nomeMedico, sade->crm, data);
    for(int i=0;i<obtemNLesoesConsulta(sade->consultas[sade->nConsultas]);i++){
        if(necessitaCirurgiaLesao(sade->lesoes[obtemIdLesaoConsulta(sade->consultas[sade->nConsultas], i)])){
            adicionaLesaoBiopsia(b, sade->lesoes[obtemIdLesaoConsulta(sade->consultas[sade->nConsultas], i)]);
        }
    }
    insereDocumentoFila(sade->fila, b, imprimeNaTelaBiopsia, imprimeEmArquivoBiopsia, desalocaBiopsia);
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("SOLICITACAO DE BIOPSIA ENVIADA PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c%*c");
}

void geraEncaminhamento(tSade* sade, tPaciente* p, char* data){
    char motivo[MAX_TAM_MOTIVO];
    char especialidade[MAX_TAM_ESPECIALIDADE];
    printf("#################### CONSULTA MEDICA #######################\n");
    printf("ESPECIALIDADE ENCAMINHADA: ");
    scanf("%[^\n]%*c", especialidade);
    printf("MOTIVO: ");
    scanf("%[^\n]%*c", motivo);
    tEncaminhamento* e=criaEncaminhamento(obtemNomePessoa(obtemInfoPaciente(p)), obtemCpfPessoa(obtemInfoPaciente(p)), sade->nomeMedico, sade->crm, data, especialidade, motivo);
    insereDocumentoFila(sade->fila, e, imprimeNaTelaEncaminhamento, imprimeEmArquivoEncaminhamento, desalocaEncaminhamento);
    printf("\nENCAMINHAMENTO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
    printf("############################################################\n");
    scanf("%*c%*c");
}

void geraRelatorioGeral(tSade* sade){
    int nPacientesAtendidos, masc, fem, outros, idadeMedia, tamLesoes, crioterapia, cirurgia;
    char c;
    masc=obtemNumeroMasculino(sade);
    fem=obtemNumeroFeminino(sade);
    outros=sade->nPacientes-(fem+masc);
    idadeMedia=obtemIdadeMedia(sade);
    tamLesoes=obtemTamMedioLesoes(sade);
    crioterapia=obtemQtdCrioterapias(sade);
    cirurgia=obtemQtdCirurgias(sade);
    nPacientesAtendidos=obtemNPacientesAtendidos(sade);
    tRelatorioGeral* r=criaRelatorioGeral(nPacientesAtendidos, masc, fem, outros, idadeMedia, tamLesoes, crioterapia, cirurgia, sade->nLesoes);
    printf("#################### RELATORIO GERAL #######################\n");
    imprimeNaTelaRelatorioGeral(r);
    while(1){
        printf("SELECIONE UMA OPCAO:\n");
        printf("(1) ENVIAR LISTA PARA IMPRESSAO\n");
        printf("(2) RETORNAR AO MENU PRINCIPAL\n");
        printf("############################################################\n");
        scanf("%c%*c", &c);
        if (c=='1')
        {
            insereDocumentoFila(sade->fila,r,imprimeNaTelaRelatorioGeral, imprimeArquivoRelatorioGeral, desalocaRelatorioGeral);
            printf("#################### RELATORIO GERAL #######################\n");
            printf("RELATÓRIO ENVIADO PARA FILA DE IMPRESSAO. PRESSIONE QUALQUER TECLA PARA RETORNAR AO MENU ANTERIOR\n");
            printf("############################################################\n");
            scanf("%*c%*c");
            break;
        }
        else if(c=='2'){
            desalocaRelatorioGeral(r);
            break;
        }    
    }
}

int obtemNumeroMasculino(tSade* sade){
    int aux=0;
    for(int i=0;i<sade->nPacientes;i++){
        if(!(strcmp("MASCULINO", obtemGeneroPessoa(obtemInfoPaciente(sade->pacientes[i]))))){
            aux++;
        }
    }
    return aux;
}

int obtemNumeroFeminino(tSade* sade){
    int aux=0;
    for(int i=0;i<sade->nPacientes;i++){
        if(!(strcmp("FEMININO", obtemGeneroPessoa(obtemInfoPaciente(sade->pacientes[i]))))){
            aux++;
        }
    }
    return aux; 
}

int obtemIdadeMedia(tSade* sade){
    int aux=0;
    for(int i=0;i<sade->nPacientes;i++){
        aux+=calculaIdadePessoa(obtemInfoPaciente(sade->pacientes[i]), sade->data);
    }
    return (aux/sade->nPacientes);
}

int obtemTamMedioLesoes(tSade* sade){
    int aux=0;
    for(int i=0;i<sade->nLesoes;i++){
        aux+=obtemTamanhoLesao(sade->lesoes[i]);
    }
    return (aux/sade->nLesoes);
}

int obtemQtdCirurgias(tSade* sade){
    int aux=0;
    for(int i=0;i<sade->nLesoes;i++){
        aux+=necessitaCirurgiaLesao(sade->lesoes[i]);
    }
    return aux;
}

int obtemQtdCrioterapias(tSade* sade){
    int aux=0;
    for(int i=0;i<sade->nLesoes;i++){
        aux+=necessitaCrioterapiaLesao(sade->lesoes[i]);
    }
    return aux;
}

int obtemNPacientesAtendidos(tSade* sade){
    int aux=0;
    for(int i=0;i<sade->nPacientes;i++){
        if(obtemNConsultasPaciente(sade->pacientes[i])>0){
            aux++;
        }
    }
    return aux;
}