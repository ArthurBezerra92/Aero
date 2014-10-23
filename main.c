#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Menu.h"
#include "Voo.h"
#include "ControleVoo.h"

Voo *lista;
Voo *start;
Voo *last;
int qtde;

int main(){
    start=last=NULL;
    char options[8][30] = {"inserir","listar","carregar","buscar","salvar","deletar","sair","carregar dado"};
    for(;;){
        switch(menuSelect(options,8," Projeto Aero ")){
            case 1: enter();break;
            case 2: listVoo();break;
            case 3: loadd();break;
            case 4: clearListVoo();break;//ordenaOrigemVoos();break;
            case 5: save();break;
            case 6: /*delete();loadEmpresaList();listEmpresaList();*/break;
            case 7: exit(0);break;
            case 8: loadDado("numero");break;
        }
            fflush(stdin);
    }
    return 0;
}
