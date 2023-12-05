#include "tSade.h"

int main(int argc, char *argv[]){

    tSade* sade = inicializaSade(argv[1]);

    menuSade(sade);

    criaBancoDeDados(sade);

    desalocaSade(sade);
    
    return 0;
}