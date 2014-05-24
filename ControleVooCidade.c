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

void setCidade(VooCidade *info,char *valor){
    if(valor=NULL){
        printf("Error Valor NULL\n");
    } else if(strlen(valor)>LOCT){
        printf("tamanho maximo de caracteres %i= \n",LOCT-1);
    } else {
        strcpy(info->cidade,valor);
    }
}

void setQtdeSair(VooCidade *info,char valor){
    if(valor=NULL){
        printf("Error Valor NULL\n");
    } else {
        info->qtdeSair = valor;
    }
}

char *getCidDado(VooCidade *info,char *dado){
    if(!strcmp(dado,"cidade"))return info->cidade;
    else if(!strcmp(dado,"qtdeSair"))return info->qtdeSair;
    else if(!strcmp(dado,"qtdeChegar"))return info->qtdeChegar;
    else {printf("error\n");return NULL;}
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

    printf("processando dados\n");
    ordenaVoo(dado);
    info=start;
    while(info){               // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
            if(startQtdeCid==NULL){
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                printf("capturou o primeiro  Nome da cidade %s\n",QtdeCid->cidade);
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
                printf("armazenou cidade na lista \n");
            }
        }
        info=info->next;
    }
}

void getOrigens(){
    Voo *info;
    VooCidade *QtdeCid;
    QtdeCid = newVooCidade();
    char *dado="origem";
    getCids(dado);
    //listCid();
    printf("processando dados\n");
    ordenaVoo(dado);
    //list();
    QtdeCid=startQtdeCid;
    while(QtdeCid){               // enquanto tiver regstros na lista
        info=start;
        while(info){
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
                if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))==0){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                    QtdeCid->qtdeSair++;
                    //listCid();
                    printf("cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeSair);
                }
            }
                printf("proximo item da lista de voos cidade %s\n",info->origem);
                info=info->next;
        }
                printf("proximo item da lista de cidades cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeSair);
                QtdeCid=QtdeCid->next;
    }
    dado = "destino";
    getCids(dado);
    ordenaVoo(dado);
    //list();
    QtdeCid=startQtdeCid;
    while(QtdeCid){               // enquanto tiver regstros na lista
        info=start;
        while(info){
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
                if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))==0){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                    QtdeCid->qtdeChegar++;
                    //listCid();
                    printf("cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
                }
            }
                printf("proximo item da lista de voos cidade %s\n",info->destino);
                info=info->next;
        }
                printf("proximo item da lista de cidades cidade %s %i\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
                QtdeCid=QtdeCid->next;
    }
    listCid();
}

void dsl_storeCid(VooCidade *i,VooCidade **start,VooCidade **last){
    VooCidade *old, *p;
    if(*last==NULL){
        i->next=NULL;
        i->prior=NULL;
        *last = i;
        *start = i;
        printf("setou as sentinelas\n");
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
    printf("\n\n");
    while(info){
        displayCid(info,dado);
        info=info->next;
    }
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
        if(!strcmp(info->situacao,"Realizado")){
            if(!strcmp(info->origem,cidade))qtdeOri++;
            if(!strcmp(info->destino,cidade))qtdeDest++;
            info=info->next;
        }
    }
    printf("\n%i decolagens e %i pousos na a cidade %s\n\n",qtdeOri,qtdeDest,cidade);
}


/** Função incompleta
@param  dado    informação para contar origem ou destino
@return void
*/
void qtdeDests(){
    //countCids("destino");
    //getCids("destino");
    //listCid();
    //countCids("origem");
    //listCid();
}

void qtdeOrigs(){
    Voo *info;
    VooCidade *QtdeCid;
    QtdeCid = newVooCidade();
    printf("processando dados\n");
    ordenaVoo("origem");
    info=start;
    while(info){                                                             // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
            if(startQtdeCid==NULL){
                strcpy(QtdeCid->cidade,info->origem);
                printf("capturou o primeiro  Nome da cidade %s\n",QtdeCid->cidade);
                QtdeCid->qtdeChegar=1;
                startQtdeCid=QtdeCid;
            }
            else if(!strcmp(QtdeCid->cidade,info->origem)){
                QtdeCid->qtdeChegar++;    //se o nome da cidade do item atual da lista for diferente ao nome da cidade da lista dos registros
                printf("%s realizou %i decolagens\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
            }
            else if(strcmp(QtdeCid->cidade,info->origem)){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                printf("armazenou na lista \n");
                QtdeCid = (VooCidade*) malloc(sizeof(VooCidade));
                if(!QtdeCid){
                    printf("\nsem memória");
                    return;
                }
                strcpy(QtdeCid->cidade,info->origem);
                printf("capturou o Nome da cidade %s\n",QtdeCid->cidade);
                QtdeCid->qtdeChegar=1;
            }
            if(info==last){
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
            }
        }
        info=info->next;
    }
    QtdeCid=startQtdeCid;
    printf("\n\n");
    while(QtdeCid){
        printf("%s realizou %i decolagens\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
        QtdeCid=QtdeCid->next;
    }
}

void qtdeVooCids(){
    VooCidade *QtdeCid;
    Voo *info;
    info=start;
    QtdeCid = (VooCidade*) malloc(sizeof(VooCidade));
    if(!QtdeCid){
        printf("\nsem memória");
        return;
    }
    startQtdeCid=QtdeCid;
    lastQtdeCid=QtdeCid;
    printf("processando dados\n");
    ordenaVoo("destino");
    while(info){                                                             // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
              if(info==start){
                strcpy(QtdeCid->cidade,info->destino);
                printf("capturou o primeiro  Nome da cidade %s\n",QtdeCid->cidade);
                QtdeCid->qtdeChegar=1;
            }
            else if(!strcmp(QtdeCid->cidade,info->destino)){
                QtdeCid->qtdeChegar++;    //se o nome da cidade do item atual da lista for diferente ao nome da cidade da lista dos registros
                printf("%s realizou %i decolagens\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
            }
            else if(strcmp(QtdeCid->cidade,info->destino)){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                QtdeCid = (VooCidade*) malloc(sizeof(VooCidade));
                if(!QtdeCid){
                    printf("\nsem memória");
                    return;
                }
                strcpy(QtdeCid->cidade,info->destino);
                printf("capturou o Nome da cidade %s\n",QtdeCid->cidade);
                QtdeCid->qtdeChegar=1;
            }
            if(info==last){
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
            }
        }
        info=info->next;
    }
    info=start;
    QtdeCid=startQtdeCid;
    ordenaVoo("origem");
    while(info){                                                             // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
            if(info==start){
                strcpy(QtdeCid->cidade,info->destino);
                printf("capturou o primeiro  Nome da cidade %s\n",QtdeCid->cidade);
                //QtdeCid->qtdeSair=1;
            }
            else if(!strcmp(QtdeCid->cidade,info->origem)){
                QtdeCid->qtdeSair++;    //se o nome da cidade do item atual da lista for diferente ao nome da cidade da lista dos registros
                printf("%s realizou %i decolagens\n",QtdeCid->cidade,QtdeCid->qtdeSair);
            }
            else if(strcmp(QtdeCid->cidade,info->origem)){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                QtdeCid = (VooCidade*) malloc(sizeof(VooCidade));
                if(!QtdeCid){
                    printf("\nsem memória");
                    return;
                }
                strcpy(QtdeCid->cidade,info->origem);
                printf("capturou o Nome da cidade %s\n",QtdeCid->cidade);
                QtdeCid->qtdeSair=1;
            }
            if(info==last){
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
            }
        }
        info=info->next;
    }
    info=start;
    QtdeCid=startQtdeCid;
    printf("\n\n");
    while(QtdeCid){
        printf("%s realizou %i decolagens\n",QtdeCid->cidade,QtdeCid->qtdeChegar);
        QtdeCid=QtdeCid->next;
        system("pause");
    }
}

/** Função que conta a quantidade de decolagens ou de pousos de uma lista de Voos
    Ela guarda as informações em outra lista com as cidades contadas
@param  dado    informação para contar origem ou destino
@return void
*/
void countCids(char *dado){
    Voo *info;

    /*char *dado;
    dado = "origem";
    qtdec = "qtdeSair";*/
    char *qtdec;
    qtdec = malloc(11*sizeof(char));
    //Condicoes para definir com que tipo de dado vamos trabalhar
    if(!strcmp(dado,"origem"))strcpy(qtdec,"qtdeSair");
    else if(!strcmp(dado,"destino"))strcpy(qtdec,"qtdeChegar");
    else {printf("Dado invalido. insira (origem) ou (destino)");return;}

    VooCidade *QtdeCid,*p,*old;
    QtdeCid = newVooCidade();
    printf("processando dados\n");
    ordenaVoo(dado);
    info=start;
    while(info){               // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
            if(startQtdeCid==NULL){
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                printf("capturou o primeiro  Nome da cidade %s\n",QtdeCid->cidade);
                setCidDado(QtdeCid,qtdec,1);
                startQtdeCid=QtdeCid;
            }

            else if(!strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))){
                setCidDado(QtdeCid,qtdec,(getCidDado(QtdeCid,qtdec)+1));
                printf("%s %s: %i \n",QtdeCid->cidade,qtdec,getCidDado(QtdeCid,qtdec));
            }
            else if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                printf("armazenou na lista \n");
                QtdeCid = newVooCidade();
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                printf("capturou o Nome da cidade %s\n",QtdeCid->cidade);
                setCidDado(QtdeCid,qtdec,1);
            }
            if(info==last)dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
        }
        info=info->next;
    }

/*    dado = "destino";
    ordenaVoo(dado);
    info=start;
    while(info){               // enquanto tiver regstros na lista
        if(!strcmp(info->situacao,"Realizado")){
            printf("situacao do Voo -> Realizado\n");
            if(startQtdeCid==NULL){
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                printf("capturou o primeiro  Nome da cidade %s\n",QtdeCid->cidade);
                setCidDado(QtdeCid,qtdec,1);
                startQtdeCid=QtdeCid;
            }
            p = startQtdeCid;
            old =NULL;
            while(p){
                if(strcmp(getCidDado(p,"cidade"),getCidDado(QtdeCid,"cidade"))<0){
                    old = p;
                    p = p->next;
                }
                else {
                    if(p->prior){
                        compareCid(QtdeCid,info,dado,qtdec);
                        p->prior->next = i;
                        i->next = p;
                        i->prior = p->prior;
                        p->prior = i;
                        return;
                    }

                    setCidDado(QtdeCid,qtdec,(getCidDado(QtdeCid,qtdec)+1));
                    printf("%s %s: %i \n",QtdeCid->cidade,qtdec,getCidDado(QtdeCid,qtdec));

                }
            }
            else if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))<0){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                printf("armazenou na lista \n");
                QtdeCid = newVooCidade();
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                printf("capturou o Nome da cidade %s\n",QtdeCid->cidade);
                setCidDado(QtdeCid,qtdec,1);
            }
            if(info==last)dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
        }
        info=info->next;
    }

*/
}

void compareCid(VooCidade *QtdeCid,Voo *info, char *dado, char *qtdec){
            if(!strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))){
                setCidDado(QtdeCid,qtdec,(getCidDado(QtdeCid,qtdec)+1));
                printf("%s %s: %i \n",QtdeCid->cidade,qtdec,getCidDado(QtdeCid,qtdec));
            }
            else if(strcmp(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado))){                                        //se s lista não tiver o nome da cidade adicione copie do item de registros atual
                dsl_storeCid(QtdeCid,&startQtdeCid,&lastQtdeCid);
                printf("armazenou na lista \n");
                QtdeCid = newVooCidade();
                strcpy(getCidDado(QtdeCid,"cidade"),getVooDado(info,dado));
                printf("capturou o Nome da cidade %s\n",QtdeCid->cidade);
                setCidDado(QtdeCid,qtdec,1);
            }
}




