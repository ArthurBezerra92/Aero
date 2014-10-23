#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VooCidade.h"
#include "Voo.h"

extern VooCidade *listaQtdeCid=NULL;
extern VooCidade *startQtdeCid=NULL;
extern VooCidade *lastQtdeCid=NULL;

Voo *lista;
Voo *start;
Voo *last;
int qtde;

void dsl_storeCid(VooCidade *i,VooCidade **start,VooCidade **last);
void QtdeVooCid(char *cidade);
void QtdeCids();

/** Função que aloca um espaco na memoria e inicializa uma struct Voo
    Atribui valores iniciais a todos os dados para evitar erros
@param  void
@return *VooCidade  retorna o endereço de memoria da struct
*/
VooCidade *newVooCidade(){
    VooCidade *info;
    info = (VooCidade*) malloc(sizeof(VooCidade));
    if(!info){
        printf("\nsem memória");
        return;
    }
    info->cidade[0] = NULL;
    info->qtdeChegar = 0;
    info->qtdeSair = 0;
}

void setCidDado(VooCidade *info,char *dado,char *valor){
    if(!strcmp(dado,"cidade"))strcpy(info->cidade,valor);
    else if(!strcmp(dado,"qtdeSair"))info->qtdeSair=valor;
    else if(!strcmp(dado,"qtdeChegar"))info->qtdeChegar=valor;
    else {printf("error\n");return NULL;}
}

char *getCidDado(VooCidade *info,char *dado){
    if(!strcmp(dado,"cidade"))return info->cidade;
    else if(!strcmp(dado,"qtdeSair"))return info->qtdeSair;
    else if(!strcmp(dado,"qtdeChegar"))return info->qtdeChegar;
    else {printf("error\n");return NULL;}
}

void displayCid(VooCidade *info,char *dado){
    if(!strcmp(dado,"cidade"))printf("Cidade\t\t%s\n",info->cidade);
    else if(!strcmp(dado,"qtdeSair"))printf("Decolagens\t%c\n",info->qtdeSair);
    else if(!strcmp(dado,"qtdeChegar"))printf("Pousos\t\t%c\n",info->qtdeChegar);
    else if(!strcmp(dado,"all")){
    printf("Cidade\t\t%s\n",info->cidade);
    printf("Decolagens\t%i\n",info->qtdeSair);
    printf("Pousos \t\t%i\n",info->qtdeChegar);
    printf("\n");
    }else return;
}

void listCid(){
    VooCidade *info;
    info = startQtdeCid;
    char *dado="all";
    printf("\n");
    if(info==NULL){
        printf("Lista Vazia\n");
        return;
    }    while(info){
        displayCid(info,dado);
        info=info->next;
    }
}

void clearListVooCid(){
    VooCidade *info;
    info=startQtdeCid;
    qtde=0;
    while(info!=lastQtdeCid){
        free(info);
        info = info->next;
    }
    startQtdeCid=lastQtdeCid=NULL;
    //printf("Lista esvaziada\n");
}

/** Função que carrega todas as informações de uma lista de Voos para uma lista de cidades
@return void
*/
void loadCidadeList(){
    Voo *info;
    VooCidade *QtdeCid;
    if(start==NULL){
        printf("Error:lista de voos vazia\n");
        return;
    }
    clearListVooCid();
    //listCid();
    QtdeCid = newVooCidade();
    char *dado="origem";
    ordenaVoo("empresa");//list();
    getCids(dado);//listCid();
    printf("processando dados\n");
    ordenaVoo(dado);//list();
    QtdeCid=startQtdeCid;
    while(QtdeCid){               // enquanto tiver regstros na lista
        info=start;
        while(info){
        if(!strcmp(info->situacao,"REALIZADO")){
            //printf("situacao do Voo -> Realizado\n");
                if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))==0){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                    QtdeCid->qtdeSair++;//listCid();
                    //printf("cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeSair);
                }
            }
                //printf("proximo item da lista de voos cidade %s\n",info->origem);
                info=info->next;
        }
                //printf("proximo item da lista de cidades cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeSair);
                QtdeCid=QtdeCid->next;
    }
    dado = "destino";
    getCids(dado);
    ordenaVoo(dado);//list();
    QtdeCid=startQtdeCid;
    while(QtdeCid){               // enquanto tiver regstros na lista
        info=start;
        while(info){
        if(!strcmp(info->situacao,"REALIZADO")){
            //printf("situacao do Voo -> Realizado\n");
                if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))==0){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                    QtdeCid->qtdeChegar++;//listCid();
                    //printf("cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
                }
            }
                //printf("proximo item da lista de voos cidade %s\n",info->destino);
                info=info->next;
        }
                //printf("proximo item da lista de cidades cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
                QtdeCid=QtdeCid->next;
    }
    //listCid();
}

/** Função copia as cidades da lista em uma lista de Voos para uma lista de cidades
@param  dado    informação para dizer de onde pegar as cidades (origem ou destino)
@return void
*/
void getCids(char *dado){
    char contem=0;
    Voo *info;
    VooCidade *QtdeCid;
    QtdeCid = newVooCidade();
    //printf("processando dados\n");
    ordenaVoo(dado);
    info=start;
    while(info){               // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"REALIZADO")){
            printf("situacao do Voo -> Realizado\n");
            if(startQtdeCid==NULL){
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                //printf("capturou o primeiro  Nome da cidade %s\n",QtdeCid->cidade);
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                startQtdeCid=QtdeCid;
            }
            QtdeCid=startQtdeCid;
             contem=0;
            while(QtdeCid){
                if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))==0){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                    contem=1;
                    break;
                }
                QtdeCid=QtdeCid->next;
            }
            if(contem==0){
                QtdeCid = newVooCidade();
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                //printf("armazenou cidade na lista \n");
            }
        }
        info=info->next;
    }
}

void dsl_storeCid(VooCidade *i,VooCidade **start,VooCidade **last){
    VooCidade *old, *p;
    if(*last==NULL){
        i->next=NULL;
        i->prior=NULL;
        *last = i;
        *start = i;
        //printf("setou as sentinelas\n");
        return;
    }
    p = *start; // começa no topo da lista
    old = NULL;
    while(p){
        if(strcmp(p->cidade, i->cidade)<0){
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

void ordenaCid(char *dado){
   VooCidade *p,*i;
   VooCidade *old=NULL;
   int t=1;
    //se a lista estiver vazia
    if(lastQtdeCid==NULL){
        i->next=NULL;
        i->prior=NULL;
        printf("Lista vazia\n");
        return;
    }
    for(p=startQtdeCid;p!=NULL;p=p->next){
       for(i=lastQtdeCid;(i!=p && i!=NULL &&i!=p->prior);i=i->prior){
           //printf("Processo %i \n",t);t++;
           //printf("destion de p %s \n",getVooDado(p,dado));
           //printf("destino de i %s \n",getVooDado(i,dado));
           if(strcmp(getCidDado(p,dado),getCidDado(i,dado))>0){
                //printf("item p é maior que item i \n");
                if(i->prior!=p)p->next->prior = i;
                if(p->next!=i)i->prior->next = p;

                if(p->prior)p->prior->next = i;     //não faz no inicio
                else {startQtdeCid=i;}

                if(i->next)i->next->prior = p;     //não faz no fim
                else {lastQtdeCid=p;}

                old = i->next;
                if(p->next==i)i->next=p;
                else i->next = p->next;
                //i->next = p->next;
                p->next = old;

                old = p->prior;
                if(i->prior==p)p->prior=i;
                else p->prior = i->prior;
                //p->prior = i->prior;
                i->prior = old;

                old=i;
                i=p;
                p=old;

                //printf("destion de p %s \n",p->destino);
                //printf("destino de i %s \n",i->destino);
                //test++;
                //if(test==4)system("pause");
                //list();
                //test++;
                //if(test==3)system("pause");
                /*printf("start e last \n",t);
                display(start);
                display(last);*/
            }// else printf("pulou\n");
        }
    }
    //list();
}

void qtdeVooCid(char *cidade){
    Voo *info;
    info=start;
    int qtdeDest=0;
    int qtdeOri=0;
    while(info){
        if(!strcmp(info->situacao,"REALIZADO")){
            if(!strcmp(info->origem,cidade))qtdeOri++;
            if(!strcmp(info->destino,cidade))qtdeDest++;
            info=info->next;
        }
    }
    printf("\n%i decolagens e %i pousos na a cidade %s\n\n",qtdeOri,qtdeDest,cidade);
}

