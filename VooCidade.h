#ifndef VOOCIDADE_H_INCLUDED
#define VOOCIDADE_H_INCLUDED

typedef struct VooCidade{
    char cidade[5];
    char qtdeSair;
    char qtdeChegar;
    struct VooCidade *next;
    struct VooCidade *prior;
} VooCidade;

#endif // VOOCIDADE_H_INCLUDED
