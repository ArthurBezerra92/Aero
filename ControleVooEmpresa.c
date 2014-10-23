#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
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

VooEmpresa *newVooEmpresa(){
    VooEmpresa *info;
    info = (VooEmpresa*) malloc(sizeof(VooEmpresa));
    if(!info){
        printf("\nsem memória");
        return;
    }
    info->empresa[0] = NULL;
    info->qtde = 0;
    info->vooTime = 0;
}

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

void loadEmpresaList(){
    time_t hSaida;             //variavel temporaria de horario de saida
    time_t hChegada;           //variavel temporaria de horario de saida
    struct tm *tempo;
    VooEmpresa *qtdeVoo;
    Voo *info;
    if(start==NULL){
        printf("Error:lista de voos vazia\n");
        return;
    }
    clearListVooEmp();//clearListVoo();
    //listEmpresaList();
    ordenaVoo("empresa");
    info=start;
    qtdeVoo = newVooEmpresa();
    printf("processando dados\n");
    while(info){                                                             // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"REALIZADO")){
            //printf("situacao do Voo -> Realizado\n");
            if(info==start){
                strcpy(qtdeVoo->empresa,info->empresa);
                //printf("capturou o primeiro  Nome da empresa %s\n",qtdeVoo->empresa);
                hSaida = mktime(&info->sr); //printf("hora saida = %i\n",hSaida);
                hChegada = mktime(&info->cr);//printf("hora chegada = %i\n",hChegada);
                qtdeVoo->vooTime += difftime(hChegada, hSaida);//printf("hora total = %i\n",qtdeVoo->vooTime);
                qtdeVoo->qtde=1;
            }
            else if(!strcmp(qtdeVoo->empresa,info->empresa)){
                hSaida = mktime(&info->sr);//printf("hora saida = %i\n",hSaida);
                hChegada = mktime(&info->cr);//printf("hora chegada = %i\n",hChegada);
                qtdeVoo->vooTime += difftime(hChegada, hSaida);//printf("hora total = %i\n",qtdeVoo->vooTime);
                qtdeVoo->qtde++;    //se o nome da empresa do item atual da lista for diferente ao nome da empresa da lista dos registros
                //printf("%s realizou %i voos\n",qtdeVoo->empresa,qtdeVoo->qtde);
            }
            else if(strcmp(qtdeVoo->empresa,info->empresa)){                                        //se s lista não tiver o nome da empresa adicione copie do item de registros atual
                dsl_storeQtde(qtdeVoo,&startQtdeVoo,&lastQtdeVoo);
                qtdeVoo = newVooEmpresa();
                strcpy(qtdeVoo->empresa,info->empresa);
                //printf("capturou o Nome da empresa %s\n",qtdeVoo->empresa);
                hSaida = mktime(&info->sr);//printf("hora saida = %i\n",hSaida);//strcpy(qtdeVoo->empresa,info->empresa);
                hChegada = mktime(&info->cr);//printf("hora chegada = %i\n",hChegada);
                qtdeVoo->vooTime = difftime(hChegada, hSaida);//printf("hora total = %i\n",qtdeVoo->vooTime);
                qtdeVoo->qtde=1;
            }
            if(info==last){
                dsl_storeQtde(qtdeVoo,&startQtdeVoo,&lastQtdeVoo);
            }
        }
        info=info->next;
    }

}

/** Função que imprime no console os dados de um registro da lista de Voos
@param  info    ponteiro da struct Voo
@return void
*/
void displayEmp(VooEmpresa *info,char *dado){
    struct tm *tempo;
    if(!strcmp(dado,"empresa"))printf("Empresa\t\t%s\n",info->empresa);
    else if(!strcmp(dado,"qtde"))printf("Numero de Voos\t%i\n",info->qtde);
    else {
    printf("Empresa\t\t%s\n",info->empresa);
    printf("Numero de Voos\t%i\n",info->qtde);
    tempo = localtime(&info->vooTime);//printf("ok\n");
    dado = asctime(tempo);//printf("ok\n");
    printf("Tempo de Voo \t%s",dado);
    printf("\n");
    }
}

void listEmpresaList(){
    VooEmpresa *info;
    info = startQtdeVoo;
    char *dado="";
    if(info==NULL){
        printf("Lista de Empresas Vazia\n");
        return;
    }
    while(info){
        displayEmp(info,dado);
        printf("\n");
        info = info->next;
    }
}

void qtdeVooEmp(char *empresa){
    Voo *info;
    info=start;
    int qtdeEmp=0;
    ordenaVooEmpresa("empresa");
    while(info){
        if((!strcmp(info->empresa,empresa) && (!strcmp(info->situacao,"Realizado"))))qtdeEmp++;
        info=info->next;
    }
    printf("\n%i voos para a empresa %s\n\n",qtdeEmp,empresa);
}

void clearListVooEmp(){
    VooEmpresa *info;
    info=startQtdeVoo;
    qtde=0;
    while(info!=lastQtdeVoo){
        free(info);
        info = info->next;
    }
    startQtdeVoo=lastQtdeVoo=NULL;
   // printf("Lista esvaziada\n");
}

void qtdeVoos(){
    VooEmpresa *info;
    loadEmpresaList();
    //listEmpresaList();
    ordenaVooEmpresa("empresa");
    printf("\n\n");
    info = startQtdeVoo;
    while(info){
        displayEmp(info,"empresa");
        displayEmp(info,"qtde");
        printf("\n\n");
        info = info->next;
    }
}

void rank(){
    char datahora[80];
    int pos=0;
    struct tm *tempo;
    VooEmpresa *qtdeVoo;
    loadEmpresaList();
    qtdeVoo=startQtdeVoo;
    ordenaVooEmpresa("vooTime");
    printf("\n");
    pos=1;
    qtdeVoo=startQtdeVoo;
    while(qtdeVoo){
        tempo = localtime(&qtdeVoo->vooTime);
           if (tempo == NULL) {
               perror("localtime");
               exit(EXIT_FAILURE);
           }
        //strftime(datahora, 80, "tempo - %H:%M:%S - dia - %d", tempo);//%x - %I:%M%p
        if(strftime(datahora, 80, "tempo - %H:%M:%S - dia - %d", tempo) == 0) {
            printf("strftime returned 0");
            exit(EXIT_FAILURE);
        }
        printf("%i -> %s realizou voos com %s\n",pos,qtdeVoo->empresa,datahora);
        qtdeVoo=qtdeVoo->next;
        pos++;
    }
    printf("\n");
}

char *getVooDadoEmp(VooEmpresa *info,char *dado){
    if(!strcmp(dado,"empresa"))return info->empresa;
    else if(!strcmp(dado,"numero"))return info->qtde;
    else if(!strcmp(dado,"di"))return info->vooTime;
    else return NULL;
}

int teste(char *dado,VooEmpresa *p, VooEmpresa *i){
    if(!strcmp("empresa",dado)){
        return (!strcmp(p->empresa,i->empresa));
    }
    else if(!strcmp("qtde",dado)){
        return p->qtde<i->qtde;
    }
    else if(!strcmp("vooTime",dado)){
        return p->vooTime<i->vooTime;
    }
    else return 0;
}

void ordenaVooEmpresa(char *dado){
   VooEmpresa *p,*i;
   VooEmpresa *old=NULL;
   int t=1;
    //se a lista estiver vazia
    if(lastQtdeVoo==NULL){
        i->next=NULL;
        i->prior=NULL;
        printf("Lista vazia\n");
        return;
    }

    for(p=startQtdeVoo;p!=NULL;p=p->next){
       for(i=lastQtdeVoo;(i!=p && i!=NULL &&i!=p->prior);i=i->prior){
           if(teste(dado,p,i)/*p->vooTime<i->vooTime*/){
                //printf("ok\n");
                if(i->prior!=p)p->next->prior = i;
                if(p->next!=i)i->prior->next = p;

                if(p->prior)p->prior->next = i;     //não faz no inicio
                else {startQtdeVoo=i;}

                if(i->next)i->next->prior = p;     //não faz no fim
                else {lastQtdeVoo=p;}

                old = i->next;
                if(p->next==i)i->next=p;
                else i->next = p->next;
                p->next = old;

                old = p->prior;
                if(i->prior==p)p->prior=i;
                else p->prior = i->prior;
                i->prior = old;

                old=i;
                i=p;
                p=old;
            }
        }
    }
}

