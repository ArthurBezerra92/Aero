#ifndef VOO_H_INCLUDED
#define VOO_H_INCLUDED
#define EMPT 4

typedef struct VooEmpresa{
    char empresa[EMPT];
    short int qtde;
    struct VooEmpresa *next;
    struct VooEmpresa *prior;
} VooEmpresa;

#endif // VOO_H_INCLUDED
