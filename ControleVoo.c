#ifndef CONTROLEVOO_H_INCLUDED
#define CONTROLEVOO_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Voo.h"
#include "functions.c"

extern Voo *lista=NULL;
extern Voo *start=NULL;
extern Voo *last=NULL;
extern int qtde=0;

void delete(Voo **, Voo **);
Voo *find(char *dado);
void display(Voo *info,char *dado);
void enter(), search(), save();
void load(), list(), list2();
void dsl_store(Voo *i, Voo **start,Voo **last);
char *getVooDado(Voo *info,char *dado);

/** Função como o processo para inserir um registro de um voo*/
void enter(){
    Voo *info;
    for(;;){
        info = (Voo*) malloc(sizeof(Voo));
        if(!info){
            printf("\nsem memória");
            return;
        }
        inputs("Insira a empresa",info->empresa,4);
        if(!info->empresa[0])break;
        inputs("Insira o numero",info->numero,5);
        inputs("Insira o DI",info->di,1);
        inputs("Insira o tipo",info->tipo,1);
        inputs("Insira a origem",info->origem,4);
        inputs("Insira o destino",info->destino,4);
        inputs("Insira o saidaP",info->saidaP,17);
        inputs("Insira o saidaR",info->saidaR,17);
        inputs("Insira o chegadaP",info->chegadaP,17);
        inputs("Insira o chegadaR",info->chegadaR,17);
        inputs("Insira a situação",info->situacao,9);
        inputs("Insira a justficativa",info->situacao,2);
        dsl_store(info, &start, &last);
        //dsa_store(info,&vector[0],qtde);
        qtde++;
        //display(&vector[0]);
    }
}

/** Função que imprime no console os dados de um registro da lista de Voos
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
    printf("\n");
    }
}

/** Função Lista todos os registros do Voos no console*/
void list(){
    Voo *info;
    info = start;
    char *dado="";
    while(info){
        display(info,dado);
        dado = asctime(&info->sp);
        printf("Struct Saida Prevista \t\t%s\n",dado);
        info = info->next;
    }
    printf("\n%i registros \n\n",qtde);
}

/**Funcao para salvar as informacoes em um arquivo de texto*/
void save(void){
    Voo *info;
    FILE *fp;
    fp = fopen("arquivo.txt","w+b");
    if(!fp){
        printf("Arquivo não pode ser aberto.\n");
        exit(1);
    }
    printf("\nsalvando arquivo\n");
    info=start;
    while(info){
        fwrite(info, sizeof(Voo),1,fp);
        info = info->next;
        }
    fclose(fp);
}

/**Funcao para carregar os registros em um arquivo de texto*/
void load(){
    char ch=0;  //*buffer,
    int i=0,u=0,a=0;
    Voo *info;
    FILE *fp;
    fp = fopen("aero.db","rb");
    if(!fp){
        printf("O arquivo não pode ser aberto.\n");
        exit(1);
    }
    while(start){
        info = start->next;
        free(info);
        start = info;
    }
    start=last=NULL;
    printf("\nloading file\n");
    //ler todo o arquivo
    while(!feof(fp)){
        info = (Voo*) malloc(sizeof(Voo));
        if(!info){        //se não der mais para alocar espaço na memória
            printf("Sem memória");
            return;
        }
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
                    case 0: if(1!=fread(info->empresa,3,1,fp))printf("error");info->empresa[3]='\0';printf("%s",info->empresa);break;
                    case 1: if(1!=fread(info->numero,4,1,fp))printf("error");info->numero[4]='\0';printf("%s",info->numero);break;
                    case 2: if(1!=fread(info->di,1,1,fp))printf("error");info->di[1]='\0';printf("%s",info->di);break;
                    case 3: if(1!=fread(info->tipo,1,1,fp))printf("error");info->tipo[1]='\0';printf("%s",info->tipo);break;
                    case 4: if(1!=fread(info->origem,4,1,fp))printf("error");info->origem[4]='\0';printf("%s",info->origem);break;// padrão modificado após o ':' precisar implementar tratamento
                    case 5: if(1!=fread(info->destino,4,1,fp))printf("error");info->destino[4]='\0';printf("%s",info->destino);break;
                    case 6: if(1!=fread(info->saidaP,17,1,fp))printf("error");info->saidaP[17]='\0';printf("%s",info->saidaP);
                        //printf("erro");
                        sscanf(info->saidaP,"%d/%d/%d %d%:%d%:%d",&info->sp.tm_mday,&info->sp.tm_mon,&info->sp.tm_year,&info->sp.tm_hour,&info->sp.tm_min,&info->sp.tm_sec);
                        info->sp.tm_mon--;
                        info->sp.tm_year+=100;
                        //printf("x%d/%dx",info->sp.tm_mday,info->sp.tm_year);
                        break;
                    case 7: if(1!=fread(info->saidaR,17,1,fp))printf("error");info->saidaR[17]='\0';printf("%s",info->saidaR);
                        sscanf(info->saidaR,"%d/%d/%d %d%:%d%:%d",&info->sr.tm_mday,&info->sr.tm_mon,&info->sr.tm_year,&info->cr.tm_hour,&info->sr.tm_min,&info->sr.tm_sec);
                        info->sr.tm_mon--;
                        info->sr.tm_year+=100;
                        break;
                    case 8: if(1!=fread(info->chegadaP,17,1,fp))printf("error");info->chegadaP[17]='\0';printf("%s",info->chegadaP);break;
                        sscanf(info->chegadaP,"%d/%d/%d %d%:%d%:%d",&info->cp.tm_mday,&info->cp.tm_mon,&info->cp.tm_year,&info->cp.tm_hour,&info->cp.tm_min,&info->cp.tm_sec);
                        info->cp.tm_mon--;
                        info->cp.tm_year+=100;
                        break;
                    case 9: if(1!=fread(info->chegadaR,17,1,fp))printf("error");info->chegadaR[17]='\0';printf("%s",info->chegadaR);break;
                        sscanf(info->chegadaR,"%d/%d/%d %d%:%d%:%d",&info->cr.tm_mday,&info->cr.tm_mon,&info->cr.tm_year,&info->cr.tm_hour,&info->cr.tm_min,&info->cr.tm_sec);
                        info->cr.tm_mon--;
                        info->cr.tm_year+=100;
                        break;
                    case 10: if(1!=fread(info->situacao,9,1,fp))printf("error");info->situacao[9]='\0';printf("%s",info->situacao);break;
                    case 11: if(1!=fread(info->jus,2,1,fp))printf("error");info->jus[2]='\0';printf("%s",info->jus);break;
                }
                i++;
            }
        }
        dsl_store(info,&start,&last);
        i=0;
        qtde++;
        if(u==4)break;
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
    char options[8][30] = {"Empresa","Lista de Empresas","Decolagens e Pousos","Categoria","Voos Atrasados","teste origens destinos","test","teste"};
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
            getOrigens();
            break;
        case 4 :
            qtdeTipos();
            //inputs("Tipo",s,1);
            //qtdeVooTipo(s);
            break;
        case 5 :
            qtdeAtraso();
            listAtraso();
            break;
        case 6 :
            qtdeOrigs();
            qtdeDests();
            break;
        case 7 :
            qtdeVooCids();
            break;
        case 8 :
            break;
        case 9 :
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

int test=0;
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

void troca(Voo *p,Voo *i,Voo *old){
                printf("item p é maior que item i \n");
                p->next->prior = i;
                i->prior->next = p;
                if(p->prior)p->prior->next = i;     //não faz no inicio
                else start=i;
                if(i->next)i->next->prior = p;     //não faz no fim
                else last=p;

                old = i->next;
                i->next = p->next;
                p->next = old;

                old = i->prior;
                i->prior = p->prior;
                p->prior = old;

                old=i;
                i=p;
                p=old;
                printf("destion de p %s \n",p->destino);
                printf("destino de i %s \n",i->destino);
                list();
                /*printf("start e last \n",t);
                display(start);
                display(last);*/

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




//difftime


#endif
