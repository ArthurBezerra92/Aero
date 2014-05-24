#include
#include
#include

typedef struct nodo{
char nome[30];
char fone[15];
struct nodo *anterior, *proximo;
}lista;

lista *primeiro, *atual, *anterior, *proximo, *gravar;

void insere(char tipo){

if(primeiro == NULL){
primeiro = malloc(sizeof(lista));
primeiro->proximo = gravar;
primeiro->anterior = gravar;
gravar->anterior = primeiro;
gravar->proximo = primeiro;
}
else{
if(tipo == 'M'){
atual = primeiro->proximo;

while(strcmp(gravar->nome,atual->nome) > 0){
if(atual != primeiro)
atual = atual->proximo;
else
break;
}
anterior = atual->anterior;

proximo = atual; /* o endereço de atual vai para proximo */

anterior->proximo = gravar; /* Os dados contidos em "gravar" serão inseridos entre */
gravar->anterior = anterior; /* as os nodos referencia "anterior" e "proximo" */
gravar->proximo = proximo;
proximo->anterior = gravar;
}
if(tipo == 'F'){
anterior = primeiro->anterior;
proximo = primeiro;

anterior->proximo = gravar; /* Os dados contidos em "gravar" serão inseridos entre */
gravar->anterior = anterior; /* as os nodos referencia "anterior" e "proximo" */
gravar->proximo = proximo;
proximo->anterior = gravar;
}
}
}

void NovoReg(void){
system("cls");

gravar = malloc(sizeof(lista));

printf("Nome: ");
gets(gravar->nome);
printf("\nFone: ");
gets(gravar->fone);


insere('M'); /* chamada do procedimento de inserção */
/* 'M' corresponde a inserção no meio ( acarretando em encadeamento ordenado) e */
/* 'F' corresponde a inserção no fim */

printf("\nSeu registro foi incluido!\n\n");
system("pause");
}

void listar(void){
char op;

if(primeiro == NULL){
system("cls");
printf("Nenhum registro armazenado...\n\n");
system("pause");
return;
}
else{

atual = primeiro->proximo;

do{
system("cls");

printf("Pressione + e - para alternar entre os registros e para sair.\n\n");

printf("Nome: %s\n\nFone: %s\n",atual->nome,atual->fone);

op = getch();

switch (op){
case 43:{
if (atual->proximo == primeiro)
atual = primeiro->proximo;
else
atual = atual->proximo;
break;
}
case 45:{
if(atual->anterior == primeiro)
atual = primeiro->anterior;
else
atual = atual->anterior;
}
}

}while(op != 27);
}
}

void excluir(void){
char op;

if(primeiro == NULL){
system("cls");
printf("Nenhum registro armazenado...\n\n");
system("pause");
return;
}
else{

atual = primeiro->proximo;

do{
system("cls");

printf("Pressione + e - para alternar entre os registros, sair e confirmar\n\n");

printf("Nome: %s\n\nFone: %s\n",atual->nome,atual->fone);

op = getch();

switch (op){
case 43:{
if (atual->proximo == primeiro)
atual = primeiro->proximo;
else
atual = atual->proximo;
break;
}
case 45:{
if(atual->anterior == primeiro)
atual = primeiro->anterior;
else
atual = atual->anterior;
}
}

}while((op != 27) && (op != 13));
}

if(op == 27)
return;

printf("\n\nVoce confirma a exclusao deste registro (S/N): [ ]\b\b");
op = getch();

if (op >= 97)
op -= 32;

if(op == 'S'){
anterior = atual->anterior;
proximo = atual->proximo;

anterior->proximo = proximo;
proximo->anterior = anterior;

free(atual);

if (primeiro == primeiro->proximo) /* se for excluido o penultimo registro, sobrando apenas o registro "primeiro" */
primeiro = NULL; /* que não é util para nós, o primeiro tambem será liberado */
printf("\n\nRegistro excluido com sucesso!\n\n");
system("pause");

}
else
return;

}

int main(void){
char escolha;

do{
system("cls");

printf("I - Inclui\nC - Consulta\nE - Exclui\n - Sair\n\nEscolha[ ]\b\b");
escolha = getch();

if(escolha >= 97)
escolha -= 32;

if(escolha == 'I')
NovoReg();
if(escolha == 'C')
listar();
if(escolha == 'E')
excluir();

}while(escolha != 27);

return 0;
}
