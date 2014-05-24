#include <stdio.h>


/** Função que ler o dado inserido pelo usuario em relação ao prompt
@param  prompt     cadeia de caracteres inserida pelo usuario
@param  count      tamanho maximo de caracteres que o dado pode ter
@return null
*/
void inputs(char *prompt,char *s, int count){
    char p[255];
    do{
        printf("%s: ",prompt);
        gets(p);
        if(strlen(p)>count)printf("\nMuito longo\n");
    }while(strlen(p)>count);
    strcpy(s,p);
    fflush(stdin);
}

/** Função que ler o dado inserido pelo usuario em relação ao prompt
@param  prompt     cadeia de caracteres inserida pelo usuario
@param  count      tamanho maximo de caracteres que o dado pode ter
@return null
*/
void floatInputs(char *prompt,float *s,int min,int max){
    float p=0;
    if(max==NULL)max=999;
    else if(min==NULL)min=-999;
    do{
        printf("%s: ",prompt);
        scanf("%f",&p);
        if(p>max)printf("%i e o valor maximo\n",max);
        else if(p<min)printf("%i e o valor minimo\n",min);
    }while(p>max || p<min);
    *s = p;
    fflush(stdin);
}

void intInputs(char *prompt,int *s, int min, int max){
    int p=0;
    if(max==NULL)max=999;
    else if(min==NULL)min=-999;
    do{
        printf("%s: ",prompt);
        scanf("%i",&p);
        if(p>max)printf("%i e o valor maximo\n",max);
        else if(p<=min)printf("%i e o valor minimo\n",min);
    }while(p>max || p<min);
    *s = p;
    fflush(stdin);
}
