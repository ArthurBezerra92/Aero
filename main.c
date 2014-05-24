#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Menu.h"
#include "Voo.h"
#include "ControleVoo.h"

//#include "Menu.c"
//#include "Voo.c"
//#include "ControleVoo.c"

Voo *lista;
Voo *start;
Voo *last;
int qtde;

int main(){
    start=last=NULL;
    char options[8][30] = {"inserir","listar","carregar","salvar","deletar","","buscar","sair"};
    for(;;){
        switch(menuSelect(options,8," Projeto Aero ")){
            case 1: enter();break;
            case 2: list();break;
            case 3: load();break;
            case 4: break;//ordenaOrigemVoos();break;
            case 5: /*delete();*/break;
            case 6: /*qtdeVoos()*/;break;
            case 7: search();break;
            case 8: exit(0);break;
            //case 9: sortVoo(&start,&last);list();break;
        }
            fflush(stdin);
    }
    return 0;
}
