#include "tSade.h"

int main(){

    tSade* sade = inicializaSade();

    menuSade(sade);

    criaBancoDeDados(sade);

    desalocaSade(sade);
    
