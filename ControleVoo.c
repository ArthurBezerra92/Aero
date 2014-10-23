#ifndef CONTROLEVOO_H_INCLUDED
#define CONTROLEVOO_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Voo.h"
#include "functions.c"
#include "arvore.c"

extern Voo *listVooa=NULL;
extern Voo *start=NULL;
extern Voo *last=NULL;
extern int qtde=0;
Trees* raiz = NULL;

void delete(Voo **, Voo **);
Voo *find(char *dado);
void display(Voo *info,char *dado);
void enter(), search(), save();
void load(), listVoo(), listVoo2();
void dsl_store(Voo *i, Voo **start,Voo **last);
char *getVooDado(Voo *info,char *dado);
void ordenaVoo(char *dado);
Voo *newVoo(void);
void clearListVoo(void);

Voo *newVoo(){
    Voo *info;
    info = (Voo*) malloc(sizeof(Voo));
    if(!info){
        printf("\nsem memória");
        return;
    }
    info->empresa[0] = NULL;
    info->numero[0] = NULL;
    info->di[0] = NULL;
    info->tipo[0] = NULL;
    info->origem[0] = NULL;
    info->destino[0] = NULL;
    info->saidaP[0] = NULL;
    info->saidaR[0] = NULL;
    info->chegadaP[0] = NULL;
    info->chegadaR[0] = NULL;
    info->situacao[0] = NULL;
    info->jus[0] = NULL;
}

/** Função como o processo para inserir um registro de um voo*/
void enter(){
    Voo *info;
    for(;;){
        info = newVoo();
        inputs("Insira a empresa",info->empresa,3);
        if(!info->empresa[0])break;     //condição de parada do laço
        inputs("Insira o numero",info->numero,8);
        inputs("Insira o DI",info->di,2);
        inputs("Insira o tipo",info->tipo,2);
        inputs("Insira a origem",info->origem,3);
        inputs("Insira o destino",info->destino,3);
        inputs("Insira o saidaP",info->saidaP,19);
        inputs("Insira o saidaR",info->saidaR,19);
        inputs("Insira o chegadaP",info->chegadaP,19);
        inputs("Insira o chegadaR",info->chegadaR,19);
        inputs("Insira a situação",info->situacao,9);
        inputs("Insira a justficativa",info->jus,2);
        /**if(sscanf(info->saidaP,"%d/%d/%d %d%:%d%:%d",&info->sp.tm_mday,&info->sp.tm_mon,&info->sp.tm_year,&info->sp.tm_hour,&info->sp.tm_min,&info->sp.tm_sec)){
        info->sp.tm_mon--;
        info->sp.tm_year-=1900;//printf("x%d/%dx",info->sp.tm_mday,info->sp.tm_year);
        }else {
            printf("\nError\n");
        }
        display(info,"all");
        printf("\nsem memória\n");
        if(info->saidaR[0]!=NULL){
        sscanf(info->saidaR,"%d/%d/%d %d%:%d%:%d",&info->sr.tm_mday,&info->sr.tm_mon,&info->sr.tm_year,&info->sr.tm_hour,&info->sr.tm_min,&info->sr.tm_sec);
        info->sr.tm_mon--;
        info->sr.tm_year+=100;
        }
        if(info->chegadaP[0]!=NULL){
        sscanf(info->chegadaP,"%d/%d/%d %d%:%d%:%d",&info->cp.tm_mday,&info->cp.tm_mon,&info->cp.tm_year,&info->cp.tm_hour,&info->cp.tm_min,&info->cp.tm_sec);
        info->cp.tm_mon--;
        info->cp.tm_year+=100;
        }
        if(info->chegadaR[0]!=NULL){
        sscanf(info->chegadaR,"%d/%d/%d %d%:%d%:%d",&info->cr.tm_mday,&info->cr.tm_mon,&info->cr.tm_year,&info->cr.tm_hour,&info->cr.tm_min,&info->cr.tm_sec);
        info->cr.tm_mon--;
        info->cr.tm_year+=100;
        }*/
        display(info,"all");
        dsl_store(info, &start, &last);
        //dsa_store(info,&vector[0],qtde);
        qtde++;
        //display(&vector[0]);
    }
}

/** Função que imprime no console os dados de um registro da listVooa de Voos
@param  info    ponteiro da struct Voo
@return void
*/
void display(Voo *info,char *dado){
    if(!strcmp(dado,"empresa"))printf("Empresa\t\t\t%s\n",info->empresa);
    else if(!strcmp(dado,"numero"))printf("Numero\t\t\t%s\n",info->numero);
    else if(!strcmp(dado,"di"))printf("DI\t\t\t%s\n",info->di);
    else if(!strcmp(dado,"tipo"))printf("Tipo\t\t\t%s\n",info->tipo);
    else if(!strcmp(dado,"origem"))printf("Origem\t\t\t%s\n",info->origem);
    else if(!strcmp(dado,"destino"))printf("Destino\t\t\t%s\n",info->destino);
    else if(!strcmp(dado,"saidaP"))printf("Saida Prevista\t\t%s\n",info->saidaP);
    else if(!strcmp(dado,"saidaR"))printf("Saida Realizada\t\t%s\n",info->saidaR);
    else if(!strcmp(dado,"chegadaP"))printf("Chegada Prevista\t%s\n",info->chegadaP);
    else if(!strcmp(dado,"chegadaR"))printf("Chegada Realizada\t%s\n",info->chegadaR);
    else if(!strcmp(dado,"situacao"))printf("Situaçao\t\t%s\n",info->situacao);
    else if(!strcmp(dado,"justificativa"))printf("Justificativa\t\t%s\n",info->jus);
    else {
/*        display(info,"empresa");
        display(info,"numero");
        display(info,"di");
        display(info,"tipo");
        display(info,"origem");
        display(info,"destino");
        display(info,"saidaP");
        display(info,"saidaR");
        display(info,"chegadaP");
        display(info,"chegadaR");
        display(info,"situacao");
        display(info,"justificativa");*/
    printf("Empresa\t\t\t%s\n",info->empresa);
    printf("Numero\t\t\t%s\n",info->numero);
    printf("DI\t\t\t%s\n",info->di);
    printf("Tipo\t\t\t%s\n",info->tipo);
    printf("Origem\t\t\t%s\n",info->origem);
    printf("Destino\t\t\t%s\n",info->destino);
    printf("Saida Prevista\t\t%s\n",info->saidaP);
    printf("Saida Realizada\t\t%s\n",info->saidaR);
    printf("Chegada Prevista\t%s\n",info->chegadaP);
    printf("Chegada Realizada\t%s\n",info->chegadaR);
    printf("Situaçao\t\t%s\n",info->situacao);
    printf("Justificativa\t\t%s\n",info->jus);
    //if(info->sp.tm_sec){
        dado = asctime(&info->sp);
        printf("Struct Saida Prevista \t\t%s",dado);
        dado = asctime(&info->sr);
        printf("Struct Saida Realizada \t\t%s",dado);
        dado = asctime(&info->cp);
        printf("Struct Chegada Prevista \t%s",dado);
        dado = asctime(&info->cr);
        printf("Struct Chegada Realizada \t%s",dado);
    //    }
    printf("\n");
    }
}

/** Função Lista todos os registros do Voos no console*/
void listVoo(){
    Voo *info;
    info = start;
    char *dado="";
    while(info){
        display(info,dado);
        printf("\n\n");
        info = info->next;
    }
    printf("\n%i registros \n\n",qtde);
}

/**Funcao para salvar as informacoes em um arquivo de texto*/
void save(void){
    Voo *info;
    FILE *fp;
    fp = fopen("arquivo.txt","ab");
    if(!fp){
        printf("Arquivo não pode ser aberto.\n");
        exit(1);
    }
    printf("\nsalvando dados\n");
    info=start;
    while(info){
        fprintf(fp,"***\nEmpresa: %s\t",info->empresa);printf("%s\n",info->empresa);
        fprintf(fp," Numero do voo: %s\t",info->numero);printf("%s\n",info->numero);
        fprintf(fp," DI: %s\t",info->di);printf("%s\n",info->di);
        fprintf(fp," Tipo: %s\t",info->tipo);printf("%s\n",info->tipo);
        fprintf(fp," Origem: %s\t",info->origem);printf("%s\n",info->origem);
        fprintf(fp," Destino: %s\n",info->destino);printf("%s\n",info->destino);
        fprintf(fp," Saida prevista: %s\n",info->saidaP);printf("%s\n",info->saidaP);
        /*info->sp.tm_mon++;
        info->sp.tm_year-=100;//printf("x%d/%dx",info->sp.tm_mday,info->sp.tm_year);
        fprintf(fp," Saida prevista: %d/%d/%d %d%:%d%:%d",&info->sp.tm_mday,&info->sp.tm_mon,&info->sp.tm_year,&info->sp.tm_hour,&info->sp.tm_min,&info->sp.tm_sec);*/
        fprintf(fp," Saida real: %s\n",info->saidaR);printf("%s\n",info->saidaR);
        /*info->sr.tm_mon++;
        info->sr.tm_year-=100;
        fprintf(fp," Saida real: %d/%d/%d %d%:%d%:%d",&info->sr.tm_mday,&info->sr.tm_mon,&info->sr.tm_year,&info->sr.tm_hour,&info->sr.tm_min,&info->sr.tm_sec);*/
        fprintf(fp," Chegada prevista: %s\n",info->chegadaP);printf("%s\n",info->chegadaP);
        /*info->cp.tm_mon++;
        info->cp.tm_year-=100;
        fprintf(fp," Chegada prevista: %d/%d/%d %d%:%d%:%d",&info->cp.tm_mday,&info->cp.tm_mon,&info->cp.tm_year,&info->cp.tm_hour,&info->cp.tm_min,&info->cp.tm_sec);*/
        fprintf(fp," Chegada real: %s\n",info->saidaP);printf("%s\n",info->saidaP);
        /*info->cr.tm_mon++;
        info->cr.tm_year-=100;
        fprintf(fp," Chegada real: %d/%d/%d %d%:%d%:%d",&info->cr.tm_mday,&info->cr.tm_mon,&info->cr.tm_year,&info->cr.tm_hour,&info->cr.tm_min,&info->cr.tm_sec);*/
        fprintf(fp," Situacao: %s\t",info->situacao);printf("%s\n",info->situacao);
        fprintf(fp," Justificativa: %s\n***\n",info->jus);printf("%s\n",info->jus);
        info = info->next;
        }
    fclose(fp);
}

/**Função que limpa a lista de registros de Voo*/
void clearListVoo(){
    Voo *info;
    info=start;
    qtde=0;
    while(info){
        free(info);
        info = info->next;
    }
    listVoo();
    start=last=NULL;
}

/**Funcao para carregar dados especificos dos registros armazenados no arquivo de texto
@param  dado    qual dado do registro para ser carregado
@return void
*/
void loadDado(char *dado){
    char inf[10][EMPT];
    char *info;
    int i = 0;
    FILE *fp;
    fp = fopen("aero2.db","rb");
    if(!fp){
        printf("O arquivo não pode ser aberto.\n");
        exit(1);
    }
    printf("\nloading file\n");
    if(!strcmp("empresa",dado)){
        while(!feof(fp)){
            //printf("%s\n","1");
            info = (char*) malloc(sizeof(char)*EMPT);
            fscanf(fp,"***\nEmpresa: %s",info);
            fseek(fp,(ftell(fp)+231),SEEK_CUR);
            printf("(%s)\n",info);
            //fscanf(fp,"%s",inf[i]);
            //printf("(%s)\n",inf[i]);
            if(!raiz)raiz = sTrees(raiz, raiz, info);
            else sTrees(raiz, raiz, info);
            //printf("%s\n","2");
            info==NULL;
            i++;
            if(i==7)break;
        }
        inorders(raiz);
    }
    else if(!strcmp(dado,"numero")){
        while(!feof(fp)){
            info = (char*) malloc(sizeof(char)*NUMT);
            fscanf(fp," Numero do voo: %s",info);
            fseek(fp,(ftell(fp)+231),SEEK_CUR);
            printf("Numero\t\t\t%s\n",info);
            if(!raiz)raiz = sTrees(raiz, raiz, info);
            else sTrees(raiz, raiz, info);
            info==NULL;
            i++;
            if(i==7)break;
        }
    }
/**    else if(!strcmp(dado,"di")){
        while(!feof(fp)){
            fscanf(fp," DI: %s",info->di);
            printf("DI\t\t\t%s\n",info->di);
        }
    }
    else if(!strcmp(dado,"tipo")){
        while(!feof(fp)){
            fscanf(fp," Tipo: %s",info->tipo);
            printf("Tipo\t\t\t%s\n",info->tipo);
        }
    }
    else if(!strcmp(dado,"origem")){
        while(!feof(fp)){
            fscanf(fp," Origem: %s",info->origem);
            printf("Origem\t\t\t%s\n",info->origem);
        }
    }
    else if(!strcmp(dado,"destino")){
        while(!feof(fp)){
            fscanf(fp," Destino: %s",info->destino);
            printf("Destino\t\t\t%s\n",info->destino);
        }
    }
    else if(!strcmp(dado,"saidaP")){
        while(!feof(fp)){
            fscanf(fp," Saida prevista: %[^\n]",info->saidaP);
            printf("Saida Prevista\t\t%s\n",info->saidaP);
        }
    }
    else if(!strcmp(dado,"saidaR")){
        while(!feof(fp)){
            fscanf(fp," Saida real: %[^\n]",info->saidaR);
            printf("Saida Realizada\t\t%s\n",info->saidaR);
        }
    }
    else if(!strcmp(dado,"chegadaP")){
        while(!feof(fp)){
            fscanf(fp," Chegada prevista: %[^\n]",info->chegadaP)
            printf("Chegada Prevista\t%s\n",info->chegadaP);
        }
    }
    else if(!strcmp(dado,"chegadaR")){
        while(!feof(fp)){
            fscanf(fp," Chegada real: %[^\n]",info->chegadaR);
            printf("Chegada Realizada\t%s\n",info->chegadaR);
        }
    }
    else if(!strcmp(dado,"situacao")){
        while(!feof(fp)){
            fscanf(fp," Situacao: %s",info->situacao);
            printf("Situaçao\t\t%s\n",info->situacao);
        }
    }
    else if(!strcmp(dado,"justificativa")){
        while(!feof(fp)){
            fscanf(fp," Justificativa: %s\n***\n",info->jus);
            printf("Justificativa\t\t%s\n",info->jus);
        }
    }
    else {
        printf("\n");
    }*/
}

/**Funcao para carregar os registros em um arquivo de texto*/
void loadd(){
    Voo *info;
    FILE *fp;
    fp = fopen("aero2.db","rb");
    if(!fp){
        printf("O arquivo não pode ser aberto.\n");
        exit(1);
    }
    clearListVoo();
    start=last=NULL;
    printf("\nloading file\n");
    //ler todo o arquivo
    while(!feof(fp)){
        info = newVoo();
        fscanf(fp,"***\nEmpresa: %s",info->empresa);printf("(%s)\n",info->empresa);
        fscanf(fp," Numero do voo: %s",info->numero);printf("(%s)\n",info->numero);
        fscanf(fp," DI: %s",info->di);printf("(%s)\n",info->di);
        fscanf(fp," Tipo: %s",info->tipo);printf("(%s)\n",info->tipo);
        fscanf(fp," Origem: %s",info->origem);printf("(%s)\n",info->origem);
        fscanf(fp," Destino: %s",info->destino);printf("(%s)\n",info->destino);
        fscanf(fp," Saida prevista: %[^\n]",info->saidaP);printf("(%s)\n",info->saidaP);
        sscanf(info->saidaP,"%d/%d/%d %d%:%d%:%d",&info->sp.tm_mday,&info->sp.tm_mon,&info->sp.tm_year,&info->sp.tm_hour,&info->sp.tm_min,&info->sp.tm_sec);
        //fscanf(fp," Saida prevista: %d/%d/%d %d%:%d%:%d",&info->sp.tm_mday,&info->sp.tm_mon,&info->sp.tm_year,&info->sp.tm_hour,&info->sp.tm_min,&info->sp.tm_sec);
        info->sp.tm_mon--;
        info->sp.tm_year-=1900;printf("x%d/%d/%dx\n",info->sp.tm_mday,info->sp.tm_mon,info->sp.tm_year);
        fscanf(fp," Saida real: %[^\n]",info->saidaR);printf("(%s)\n",info->saidaR);
        sscanf(info->saidaR,"%d/%d/%d %d%:%d%:%d",&info->sr.tm_mday,&info->sr.tm_mon,&info->sr.tm_year,&info->sr.tm_hour,&info->sr.tm_min,&info->sr.tm_sec);
        //fscanf(fp," Saida real: %d/%d/%d %d%:%d%:%d",&info->sr.tm_mday,&info->sr.tm_mon,&info->sr.tm_year,&info->sr.tm_hour,&info->sr.tm_min,&info->sr.tm_sec);
        info->sr.tm_mon--;
        info->sr.tm_year-=1900;printf("x%d/%d/%dx\n",info->sr.tm_mday,info->sr.tm_mon,info->sr.tm_year);
        fscanf(fp," Chegada prevista: %[^\n]",info->chegadaP);printf("(%s)\n",info->chegadaP);
        sscanf(info->chegadaP,"%d/%d/%d %d%:%d%:%d",&info->cp.tm_mday,&info->cp.tm_mon,&info->cp.tm_year,&info->cp.tm_hour,&info->cp.tm_min,&info->cp.tm_sec);
        //fscanf(fp," Chegada prevista: %d/%d/%d %d%:%d%:%d",&info->cp.tm_mday,&info->cp.tm_mon,&info->cp.tm_year,&info->cp.tm_hour,&info->cp.tm_min,&info->cp.tm_sec);
        info->cp.tm_mon--;
        info->cp.tm_year-=1900;printf("x%d/%d/%dx\n",info->cp.tm_mday,info->cp.tm_mon,info->cp.tm_year);
        fscanf(fp," Chegada real: %[^\n]",info->chegadaR);printf("(%s)\n",info->chegadaR);
        sscanf(info->chegadaR,"%d/%d/%d %d%:%d%:%d",&info->cr.tm_mday,&info->cr.tm_mon,&info->cr.tm_year,&info->cr.tm_hour,&info->cr.tm_min,&info->cr.tm_sec);
        //fscanf(fp," Chegada real: %d/%d/%d %d%:%d%:%d",&info->cr.tm_mday,&info->cr.tm_mon,&info->cr.tm_year,&info->cr.tm_hour,&info->cr.tm_min,&info->cr.tm_sec);
        info->cr.tm_mon--;
        info->cr.tm_year-=1900;printf("x%d/%d/%dx\n",info->cr.tm_mday,info->cr.tm_mon,info->cr.tm_year);
        fscanf(fp," Situacao: %s",info->situacao);printf("%s\n",info->situacao);
        fscanf(fp," Justificativa: %s\n***\n",info->jus);printf("%s\n",info->jus);
        dsl_store(info,&start,&last);
        qtde++;
        printf("%i\n",qtde);
       if(feof(fp))break;
       //if(qtde==30)break;
    }
    printf("\n");
    fclose(fp);
}

void load(){
    char ch=0;  //*buffer,
    int i=0,u=0,a=0;
    Voo *info;
    FILE *fp;
    fp = fopen("aero2.db","rb");
    if(!fp){
        printf("O arquivo não pode ser aberto.\n");
        exit(1);
    }
    info=start;
    qtde=0;
    while(info){
        free(info);
        info = info->next;
    }
    start=last=NULL;
    printf("\nloading file\n");
    //ler todo o arquivo
    while(!feof(fp)){
        info = newVoo();
        while(i<12){
            ch = fgetc(fp);
            //printf("*");
            printf("%c",ch);
            if(ch==':'){
                //if(ch!=' ')
                ch=fgetc(fp);printf("%c",ch);
                //if(isspace(ch))printf("carac esp");
                fflush(stdin);
                switch(i){
                    case 0: if(1!=fread(info->empresa,EMPT,1,fp))printf("error");info->empresa[EMPT]='\0';printf("(%s)",info->empresa);break;
                    //case 1: if(1!=fread(info->numero,NUMT,1,fp))printf("error");info->numero[NUMT]='\0';printf("(%s)",info->numero);break;
                   // case 2: if(1!=fread(info->di,DTT-1,1,fp))printf("error");info->di[DTT]='\0';printf("%s",info->di);break;
 /*                   case 3: if(1!=fread(info->tipo,TIT-1,1,fp))printf("error");info->tipo[TIT]='\0';printf("%s",info->tipo);break;
                    case 4: if(1!=fread(info->origem,LOCT-1,1,fp))printf("error");info->origem[LOCT]='\0';printf("%s",info->origem);break;// padrão modificado após o ':' precisar implementar tratamento
                    case 5: if(1!=fread(info->destino,LOCT-1,1,fp))printf("error");info->destino[LOCT]='\0';printf("%s",info->destino);break;
                    case 6: if(1!=fread(info->saidaP,DATAT-1,1,fp))printf("error");info->saidaP[DATAT]='\0';printf("%s",info->saidaP);
                        //printf("erro");
                        //sscanf(info->saidaP,"%d/%d/%d %d%:%d%:%d",&info->sp.tm_mday,&info->sp.tm_mon,&info->sp.tm_year,&info->sp.tm_hour,&info->sp.tm_min,&info->sp.tm_sec);
                        //info->sp.tm_mon--;
                        //info->sp.tm_year+=100;//printf("x%d/%dx",info->sp.tm_mday,info->sp.tm_year);
                        break;
                    case 7: if(1!=fread(info->saidaR,DATAT-1,1,fp))printf("error");info->saidaR[DATAT]='\0';printf("%s",info->saidaR);
                        //sscanf(info->saidaR,"%d/%d/%d %d%:%d%:%d",&info->sr.tm_mday,&info->sr.tm_mon,&info->sr.tm_year,&info->sr.tm_hour,&info->sr.tm_min,&info->sr.tm_sec);
                        //info->sr.tm_mon--;
                        //info->sr.tm_year+=100;
                        break;
                    case 8: if(1!=fread(info->chegadaP,DATAT-1,1,fp))printf("error");info->chegadaP[DATAT]='\0';printf("%s",info->chegadaP);
                        //sscanf(info->chegadaP,"%d/%d/%d %d%:%d%:%d",&info->cp.tm_mday,&info->cp.tm_mon,&info->cp.tm_year,&info->cp.tm_hour,&info->cp.tm_min,&info->cp.tm_sec);
                        //info->cp.tm_mon--;
                        //info->cp.tm_year+=100;
                        break;
                    case 9: if(1!=fread(info->chegadaR,DATAT-1,1,fp))printf("error");info->chegadaR[DATAT]='\0';printf("%s",info->chegadaR);
                        //sscanf(info->chegadaR,"%d/%d/%d %d%:%d%:%d",&info->cr.tm_mday,&info->cr.tm_mon,&info->cr.tm_year,&info->cr.tm_hour,&info->cr.tm_min,&info->cr.tm_sec);
                        //info->cr.tm_mon--;
                        //info->cr.tm_year+=100;
                        break;
                    case 10: if(1!=fread(info->situacao,SIT-1,1,fp))printf("error");info->situacao[SIT]='\0';printf("%s",info->situacao);break;
                    case 11: if(1!=fread(info->jus,JUST-1,1,fp))printf("error");info->jus[JUST]='\0';printf("%s",info->jus);break;*/
                }
                i++;
            }
        }
        dsl_store(info,&start,&last);
        i=0;
        qtde++;
        if(u==3)break;
        if(feof(fp))break;
        u++;
    }
    printf("\n");
    fclose(fp);
}

/**Funcao de busca na lista dos registros de Voos*/
void search(){
    int i;
    char s[80];
    char *mensagem = "Digite o modo de busca";
    char options[8][30] = {"Empresa","Lista de Empresas","Decolagens e Pousos","Categoria","Voos Atrasados","Rank por Tempo de Voo","test","teste"};
    switch(menuSelect(options,8,mensagem)){
        case 1 :
            printf("Empresa : ");
            scanf("%s[^\n]",&s);
            qtdeVooEmp(s);
            break;
        case 2 :
            qtdeVoos();
            break;
        case 3 :
            loadCidadeList();
            listCid();
            break;
        case 4 :
            qtdeTipos();
            break;
        case 5 :
            listAtraso();
            qtdeAtraso();
            break;
        case 6 :
            rank();
            break;
        case 7 :
            break;
    }

}

void dsl_store(Voo *i,Voo **start,Voo **last){
    Voo *old, *p;
    //se a lista estiver vazia
    if(*last==NULL){
        i->next=NULL;
        i->prior=NULL;
        *last = i;
        *start = i;
        return;
    }
    p = *start; /* começa no topo da lista*/
    old = NULL;
    while(p){
        //se o dado anterior for menor que o novo dado
        if(strcmp(p->empresa, i->empresa)<0){
            old = p;        //atribui a uma variavel auxiliar
            p = p->next;    //atribui a p o elemento posterior a p
        }
        else{
            //Se nao estiver no inicio da lista
            if(p->prior){
                // coloca o i (novo elemento) na frente de p
                p->prior->next = i; //atribui o elemento posterior do elemento anterior a p a i //ou seja faz o elemento anterior a p apontar  para i
                i->next = p;        //atribui o elemento posterior de i a p // ou seja faz o elemento i apontap para p
                i->prior = p->prior;//atribui o elemento anterior de i ao anterior de p // ou seja faz o elemento i apontar  para o anterior de p
                p->prior = i;       //atribui o elemento anterior de p a i // ou seja faz o elemento p apontar  para i
                return;
            }
            //executa se estiver no inicio da lista
            i->next =p;
            i->prior = NULL;
            p->prior = i;
            *start =i;
            return;
        }
    }
    //executa quando está no fim da lista
    old->next=i;
    i->next=NULL;
    i->prior=old;
    *last=i;
}

/*void dsldelete(Voo *i,Voo **start,Voo **last){
    if(i->prior)i->prior->next = i->next;
    else {
        //* novo primeiro item /
        *start = i->next;
        if(start)start->prior = NULL;
    }
    if(i->next)i->next->prior = i->prior;
    else /* apaga o ultimo elemento /
        *last = i->prior;
    free(i);
}*/

void ordenaVoo(char *dado){
   Voo *p,*i;
   Voo *old=NULL;
   int t=1;
    //se a lista estiver vazia
    if(last==NULL){
        i->next=NULL;
        i->prior=NULL;
        printf("Lista vazia\n");
        return;
    }
    for(p=start;p!=NULL;p=p->next){
       for(i=last;(i!=p && i!=NULL &&i!=p->prior);i=i->prior){
           //printf("Processo %i \n",t);t++;
           //printf("destion de p %s \n",getVooDado(p,dado));
           //printf("destino de i %s \n",getVooDado(i,dado));
           if(strcmp(getVooDado(p,dado),getVooDado(i,dado))>0){
                //printf("item p é maior que item i \n");
                if(i->prior!=p)p->next->prior = i;
                if(p->next!=i)i->prior->next = p;

                if(p->prior)p->prior->next = i;     //não faz no inicio
                else {start=i;}

                if(i->next)i->next->prior = p;     //não faz no fim
                else {last=p;}

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

char *getVooDado(Voo *info,char *dado){
    if(!strcmp(dado,"empresa"))return info->empresa;
    else if(!strcmp(dado,"numero"))return info->numero;
    else if(!strcmp(dado,"di"))return info->di;
    else if(!strcmp(dado,"tipo"))return info->tipo;
    else if(!strcmp(dado,"origem"))return info->origem;
    else if(!strcmp(dado,"destino"))return info->destino;
    else if(!strcmp(dado,"saidaP"))return info->saidaP;
    else if(!strcmp(dado,"saidaR"))return info->saidaR;
    else if(!strcmp(dado,"chegadaP"))return info->chegadaP;
    else if(!strcmp(dado,"chegadaR"))return info->chegadaR;
    else if(!strcmp(dado,"situacao"))return info->situacao;
    else if(!strcmp(dado,"justificativa"))return info->jus;
    else return NULL;
}

void qtdeAtraso(){
    Voo *info;
    info = start;
    int qtde=0;
    char *dado="all";
    while(info){
    if(strcmp(info->chegadaR,info->chegadaP)>0){
        qtde++;
        }
        info = info->next;
    }
    printf("\n%i atrasos \n\n",qtde);
}

void listAtraso(){
    Voo *info;
    info = start;
    int qtde =0;
    char *dado="all";
    while(info){
        if(strcmp(info->chegadaR,info->chegadaP)>0){
            display(info,dado);
            qtde++;
        }
        info = info->next;
    }
    printf("\n%i registros \n\n",qtde);
}



#endif
