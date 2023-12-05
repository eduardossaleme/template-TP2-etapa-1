#include "tConsulta.h"

struct tConsulta{
    char data[11];
    char crmMedico[13];
    char nomeMedico[100];
    int numeroLesoesCadastradas, id;
    int *idLesao;
};