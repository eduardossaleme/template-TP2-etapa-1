#include "tPaciente.h"

struct tPaciente{
    tPessoa* info;
    int nLesoes, idade, diabetes, fumante, cancer, alergia;
    char tipoPele[3];
    tLesao** lesoes;
};