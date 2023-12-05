#include "tConsulta.h"

struct tConsulta{
    char data[11];
    char crmMedico[13];
    char nomeMedico[100];
    tPessoa* paciente;
    int numeroLesoesCadastradas;
    tLesao** lesoescadstradas;
};