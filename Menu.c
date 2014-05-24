#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int menu_select();

int menu_select(){
    char s[80];
    char c;
    printf("1 inserir:\n");
    printf("2 listar:\n");
    printf("3 carregar:\n");
    printf("4 salvar:\n");
    printf("5 buscar:\n");
    printf("6 deletar:\n");
    printf("7 sair:\n");
    do{
        printf("Digite sua escolha\n");
        gets(s);
        c = atoi(s);
    }while(c<0||c>9);
    fflush(stdin);
    return c;
}

/** Função que gera um menu simples
@param  item    vetor de strings composto pelas opcoes do menu
@param  count   quantidade de itens do vetor
@return c       caractere digitado pelo usuario
*/

int menuSelect(char item[][30] ,int count, char *mensagem){
    char s[80];
    char c;
    int i;
    if(!*mensagem==NULL)printf("%s\n",mensagem);
    for(i=1;i<=count;i++){
        printf("%i %s\n",i,item[i-1]);
    }
    do{
        printf("Digite sua escolha\n");
        gets(s);
        c = atoi(s);
    }while(c<0||c>count);
    fflush(stdin);
    return c;
}

#endif // MENU_H_INCLUDED
