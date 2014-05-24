#ifndef VOO_H_INCLUDED
#define VOO_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#define EMPT 4
#define NUMT 5
#define DTT 2
#define LOCT 5
#define DATAT 18
#define SIT 10
#define JUST 3

typedef struct Voo{
    char empresa[EMPT];
    char numero[NUMT];
    char di[DTT];
    char tipo[DTT];
    char origem[LOCT];
    char destino[LOCT];
    char saidaP[DATAT];        //Data e hora da saida prevista do voo
    char saidaR[DATAT];        //Data e hora da saida prevista do voo
    char chegadaP[DATAT];      //Data e hora da chegada prevista do voo
    char chegadaR[DATAT];      //Data e hora da chegada prevista do voo
    char situacao[SIT];
    char jus[JUST];
    struct Voo *next;
    struct Voo *prior;
} Voo;

#endif // VOO_H_INCLUDED
