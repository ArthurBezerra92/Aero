#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VooEmpresa.h"
#include "Voo.h"

extern VooEmpresa *listaQtdeVoo=NULL;
extern VooEmpresa *startQtdeVoo=NULL;
extern VooEmpresa *lastQtdeVoo=NULL;

Voo *lista;
Voo *start;
Voo *last;
int qtde;

void dsl_storeQtde(VooEmpresa *i,VooEmpresa **start,VooEmpresa **last);
void qtdeVooEmp(char *empresa);
void qtdeVoos();

void dsl_storeQtde(VooEmpresa *i,VooEmpresa **start,VooEmpresa **last){
    VooEmpresa *old, *p;
    if(*last==NULL){
        i->next=NULL;
        i->prior=NULL;
        *last = i;
        *start = i;
        return;
    }
    p = *start; // começa no topo da lista
    old = NULL;
    while(p){
        if(strcmp(p->empresa, i->empresa)<0){
            old = p;
            p = p->next;
        }
        else{
            if(p->prior){
                p->prior->next = i;
                i->next = p;
                i->prior = p->prior;
                p->prior = i;
                return;
            }
            i->next =p;
            i->prior = NULL;
            p->prior = i;
            *start =i;
            return;
        }
    }
    old->next = i;
    i->next = NULL;
    i->prior = old;
    *last = i;
}

void qtdeVooEmp(char *empresa){
    Voo *info;
    info=start;
    int qtdeEmp=0;
    while(info){
        if((!strcmp(info->empresa,empresa) && (!strcmp(info->situacao,"Realizado"))))qtdeEmp++;
        info=info->next;
    }
    printf("\n%i voos para a empresa %s\n\n",qtdeEmp,empresa);
}

void qtdeVoos(){
    VooEmpresa *qtdeVoo;
    Voo *info;
    info=start;
    qtdeVoo = (VooEmpresa*) malloc(sizeof(VooEmpresa));
    //startQtdeVoo=qtdeVoo;
    //lastQtdeVoo=qtdeVoo;
    if(!qtdeVoo){
        printf("\nsem memória");
        return;
    }
    printf("processando dados\n");
    while(info){                                                             // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
            if(info==start){
                strcpy(qtdeVoo->empresa,info->empresa);
                printf("capturou o primeiro  Nome da empresa %s\n",qtdeVoo->empresa);
                qtdeVoo->qtde=1;
            }
            else if(!strcmp(qtdeVoo->empresa,info->empresa)){
                qtdeVoo->qtde++;    //se o nome da empresa do item atual da lista for diferente ao nome da empresa da lista dos registros
                printf("%s realizou %i voos\n",qtdeVoo->empresa,qtdeVoo->qtde);
            }
            else if(strcmp(qtdeVoo->empresa,info->empresa)){                                        //se s lista não tiver o nome da empresa adicione copie do item de registros atual
                dsl_storeQtde(qtdeVoo,&startQtdeVoo,&lastQtdeVoo);
                qtdeVoo = (VooEmpresa*) malloc(sizeof(VooEmpresa));
                if(!qtdeVoo){
                    printf("\nsem memória");
                    return;
                }
                strcpy(qtdeVoo->empresa,info->empresa);
                printf("capturou o Nome da empresa %s\n",qtdeVoo->empresa);
                qtdeVoo->qtde=1;
            }
            if(info==last){
                dsl_storeQtde(qtdeVoo,&startQtdeVoo,&lastQtdeVoo);
            }
        }
        info=info->next;
    }
    qtdeVoo=startQtdeVoo;
    printf("\n\n");
    while(qtdeVoo){
        printf("%s realizou %i voos\n",qtdeVoo->empresa,qtdeVoo->qtde);
        qtdeVoo=qtdeVoo->next;
    }
}

