#ifndef VOOEMPRESA_H_INCLUDED
#define VOOEMPRESA_H_INCLUDED
#define EMPT 4

typedef struct VooEmpresa{
    char empresa[EMPT];
    short int qtde;
    int vooTime;
    struct VooEmpresa *next;
    struct VooEmpresa *prior;
} VooEmpresa;

#endif // VOOEMPRESA_H_INCLUDED
