#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Voo.h"
#include "ControleVoo.h"

Voo *lista;
Voo *start;
Voo *last;
int qtde;

void qtdeVooTipo(char *tipo);

void qtdeVooTipo(char *tipo){
    Voo *info;
    info=start;
    int qtdeTipo=0;
    while(info){
        if((!strcmp(info->tipo,tipo) && (!strcmp(info->situacao,"Realizado"))))qtdeTipo++;
        info=info->next;
    }
    printf("\n%i voos do tipo %s\n\n",qtdeTipo,tipo);
}

void qtdeTipos(){
    char tipo[2];
    int qtde=0;
    Voo *info;
    ordenaVoo("tipo");
    info=start;
    printf("\n");
    while(info){                                                             // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            if(info==start){
                strcpy(tipo,info->tipo);
                qtde=1;
            }else if(!strcmp(tipo,info->tipo)){
                qtde++;
            }
            else if(strcmp(tipo,info->tipo)){                                        //se s lista não tiver o nome da empresa adicione copie do item de registros atual
                printf("realizados %i voos da categoria %s \n",qtde,tipo);
                strcpy(tipo,info->tipo);
                qtde=1;
            }
            if(info==last){
                printf("realizados %i voos da categoria %s \n",qtde,tipo);
            }
        }
        info=info->next;
    }
    printf("\n");
}

