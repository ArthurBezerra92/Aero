/**void searchArray(){
    int i;
    char s[80];
    static char item[][30] = {"qtde voo por empresa", "qtde voos", ""};
    printf("Digite o modo de busca\n");
    switch(menuSelect(item,11)){
        case 1 :
            printf("Empresa : ");
            scanf("%s[^\n]",&s);
            qtdeVooEmp(s);
            break;
        case 2 :
            qtdeVoos();
            break;
        case 3 :
            //qtdeVooCidade();
            break;
    }

}





void listArray(){
    int i=0;
    //i=sizeof(Voo);i
    //printf("%i",i);
    //Voo *info=NULL;
    //info=vector;
    while(i<qtde){
        //info=vector+(i*sizeof(Voo)));
        //printf("%i",info);
        display(&vector[i]);
        i++;
    }
    printf("\n%i registros \n\n",qtde);
}

*/
