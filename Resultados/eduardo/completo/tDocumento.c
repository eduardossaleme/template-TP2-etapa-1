#include "tDocumento.h"
#include <stdlib.h>

struct tDocumento{
    func_ptr_desaloca fpDesaloca;
    func_ptr_imprimeEmArquivo fpImprimeArquivo;
    func_ptr_imprimeNaTela fpImprimeTela;
    void* dado;
};

tDocumento *criaDocumento(void *dado, func_ptr_imprimeNaTela imprimeNaTela,
                          func_ptr_imprimeEmArquivo ImprimeEmArquivo,func_ptr_desaloca desaloca){
    
    tDocumento* doc=(tDocumento*)malloc(sizeof(tDocumento));
    doc->dado=dado;
    doc->fpDesaloca=desaloca;
    doc->fpImprimeArquivo=ImprimeEmArquivo;
    doc->fpImprimeTela=imprimeNaTela;
    return doc;
}

void desalocaDocumento(tDocumento *doc){
    doc->fpDesaloca(doc->dado);
    free(doc);
}

void imprimeNaTelaDocumento(tDocumento *doc){
    doc->fpImprimeTela(doc->dado);
}

void imprimeEmArquivoDocumento(tDocumento *doc, char *path){
    doc->fpImprimeArquivo(doc->dado, path);
}