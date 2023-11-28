#include "tMedico.h"

struct tMedico{
    tPessoa* info;
    char usuario[MAX_TAM_LOGIN];
    char senha[MAX_TAM_LOGIN];
    char crm[13];
};