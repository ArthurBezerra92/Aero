/* Tree */
#include <string.h>

typedef struct{
	char* info;
	struct Tree* left;
	struct Tree* right;
}Tree;

extern Tree *raiz;

Tree* stree(Tree* root, Tree* r, char *info){
  if (!r){
    r = (Tree*) malloc(sizeof(Tree));
    if (!r){
      printf("Sem memoria\n");
      exit(0);
    }
    r->left = NULL;
    r->right = NULL;
    strcpy(r->info,info);
    if(!root){printf("raiz da arvore %s\n",r->info);return r;}
    printf("comparacao %i\n",strcmp(info,root->info));
    if (strcmp(info,root->info)<0){
      printf("esquerda\n");
      root->left = r;
    }
    else{
      printf("direita\n");
      root->right = r;
    }
    printf("%s\n",r->info);
    return r;
  }
  if (strcmp(info,root->info)<0){
    stree(r,r->left, info);
  }
  else{
    stree(r,r->right, info);
  }
}

void inorder(Tree* r){
  if (!r){
    //printf("arvore vazia\n");
    return;
  }
  inorder(r->left);
  if (r->info){
    printf("%s\n",r->info);
  }
  inorder(r->right);
}

void preorder(Tree* r){
  if (!r){
    return ;
  }
  if (r->info){
    printf("%c\n",r->info);
  }
  preorder(r->left);
  preorder(r->right);
}

void posorder(Tree* r)
{

  if (!r)
  {
    return ;
  }
  posorder(r->left);
  posorder(r->right);
  if (r->info)
  {
    printf("%c\n",r->info);
  }
}

Tree* searchTree(char *info, Tree* root)
{

  if (!root)
  {
    return ;
  }
  while (info!=root->info)
  {
    if (strcmp(info,root->info)<0)
    {
      root = root->left;
    }
    else
    {
      root = root->right;
    }
    if (root==NULL)
    {
      break;
    }
  }
  return root;
}

Tree* dTree(char *info, Tree* root)
{
  Tree* p;
  Tree* p2;

  if (!root)
  {
    /* nao encontrado */
    return ;
  }
  if (!strcmp(root->info,info))
  {
    /* isso significa uma arvore vazia */
    if (root->left==root->right)
    {
      free(root);
      return NULL;
    }
    /* ou se uma subarvore e nula */
    if (root->left==NULL)
    {
      p = root->right;
      return p;
    }
    else
    {
      if (root->right == NULL)
      {
        p = root->left;
        return p;
      }
      else
      {
        /* ou as duas subarvores estao presentes */
        p2 = root->right;
        p = root->right;
        while (p->left)
        {
          p = p->left;
        }
        p->left = root->left;
        free(root);
        return p2;
      }
    }
  }
  if (strcmp(root->info,info)<0)
  {
    root->right = dTree(root->right,info);
  }
  else
  {
    root->left = dTree(root->info, info);
  }
  return root;
}

