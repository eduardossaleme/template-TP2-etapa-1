#include "tFila.h"
#include <stdlib.h>

struct tFila{
    tDocumento** documentos;
    int nDocumentos;
};

tFila *criaFila(){
    tFila* fila = (tFila*)calloc(1, sizeof(tFila));
    fila->documentos=NULL;
    return fila;
}

void desalocaFila(tFila *f){
    for(int i=0;i<f->nDocumentos;i++){
        desalocaDocumento(f->documentos[i]);
    }
    if(f->documentos!=NULL) free(f->documentos);
    free(f);
}

void insereDocumentoFila(tFila *f, void *dado, func_ptr_imprimeNaTela imprimeNaTela, func_ptr_imprimeEmArquivo ImprimeEmArquivo, func_ptr_desaloca desaloca){
    f->documentos=(tDocumento**)realloc(f->documentos,(1+f->nDocumentos)*sizeof(tDocumento*));
    f->documentos[f->nDocumentos]=criaDocumento(dado, imprimeNaTela, ImprimeEmArquivo, desaloca);
    f->nDocumentos++;
}

int quantidadeDocumentosNaFila(tFila *f){
    return f->nDocumentos;
}

void imprimeFila(tFila *f, char *path){
    for(int i=0;i<f->nDocumentos;i++){
        imprimeNaTelaDocumento(f->documentos[i]);
        imprimeEmArquivoDocumento(f->documentos[i], path);
    }
}