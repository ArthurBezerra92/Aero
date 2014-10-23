#include <stdlib.h>
#include <string.h>

typedef struct Tree {
    char info;
    struct Tree *left;
    struct Tree *right;
}Tree;

typedef struct Trees {
    char info[80];
    struct Trees *left;
    struct Trees *right;
}Trees;

extern Tree *root;
extern Trees *raiz;

void inorders(Trees* r);
void preorders(Trees* r);
void posorders(Trees* r);

Tree *stree(Tree *root, Tree *r, char info){
    if(!r){
        r = (Tree*) malloc(sizeof(Tree));
        if(!r){
            printf("Sem memoria\n");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->info = info;
        if(!root)return r; //primeira entrada
        if(info<root->info)root->left = r;
        else root->right = r;
        return r;
    }
    if(info<r->info)stree(r,r->left, info);
    else stree(r,r->right, info);
}

void inorder(Tree *root){
    if(!root)return;
    inorder(root->left);
    if(root->info)printf("%c\n",root->info);
    inorder(root->right);
}

void preorder(Tree *root){
    if(!root)return;
    if(root->info)printf("%c\n",root->info);
    preorder(root->left);
    preorder(root->right);
}

void posorder(Tree *root){
    if(!root)return;
    posorder(root->left);
    posorder(root->right);
    if(root->info)printf("%c\n",root->info);
}

void print_tree(Tree *root, int l){
    int i;
    if(!root)return;
    print_tree(root->right, l+1);
    for(i=1;i<l;++i)printf(" ");
    printf("%c\n",root->info);
    print_tree(root->left,l+1);
}

Tree *searchTree(Tree *root, char key){
    if(!root)return root;   /*not found*/
    while(root->info!=key){ /*arvore vazia*/
        if(key<root->info)root = root->left;
        else root = root->right;
        if(root==NULL)break;
    }
    return root;
}

Tree *dtree(Tree *root, char key){
    Tree *p, *p2;
    if(!root)return root;   /*não encontrado*/
    if(root->info==key){   /* apagar a raiz */
        /*isso significa uma arvore vazia*/
        if(root->left==root->right){
            free(root);
            return NULL;
        }
        /*ou se uma subarvore e nula*/
        else if(root->left==NULL){
            p = root->right;
            free(root);
            return p;
        }
        else if(root->right==NULL){
            p = root->right;
            free(root);
            return p;
        }
        else {
            p2 = root->right;
            p = root->right;
            while(p->left)p = p->left;
            p->left = root->left;
            free(root);
            return p2;
        }
    }
    if(root->info<key)root->right = dtree(root->right, key);
    else root->left = dtree(root->left, key);
    return root;
}

Trees* sTrees(Trees* raiz, Trees* r, char info[]){
  if (!r){              /* raiz vazia */
    r = (Trees*) malloc(sizeof(Trees));
    if (!r){
      printf("Sem memoria\n");
      exit(0);
    }
    printf("%s\n",info);
    r->left = NULL;
    r->right = NULL;
    strcpy(r->info,info);
    if(!raiz){/*printf("raiz da arvore %s\n",r->info);*/return r;}  /* primeira inserção */
    //printf("comparacao %i\n",strcmp(info,raiz->info));
    if (strcmp(info,raiz->info)<0){
      //printf("esquerda\n");
      raiz->left = r;
    }
    else{
      //printf("direita\n");
      raiz->right = r;
    }
    //printf("%s\n",r->info);
    return r;
  }
  if (strcmp(info,raiz->info)<0){
    sTrees(r,r->left, info);
  }
  else{
    sTrees(r,r->right, info);
  }
}

void inorders(Trees* r){
  if (!r){
    //printf("arvore vazia\n");
    return;
  }
  inorders(r->left);
  if (r->info){
    printf("%s\n",r->info);
  }
  inorders(r->right);
}

void preorders(Trees* r){
  if (!r){
    return ;
  }
  if (r->info){
    printf("%s\n",r->info);
  }
  preorders(r->left);
  preorders(r->right);
}

void posorders(Trees* r)
{

  if (!r)
  {
    return ;
  }
  posorders(r->left);
  posorders(r->right);
  if (r->info)
  {
    printf("%s\n",r->info);
  }
}

Trees* searchTrees(char *info, Trees* root)
{

  if (!raiz)
  {
    return ;
  }
  while (strcpy(root->info,info))
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

Trees* dTrees(char *info, Trees* root)
{
  Trees* p;
  Trees* p2;

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
    root->right = dTrees(root->right,info);
  }
  else
  {
    root->left = dTrees(root->info, info);
  }
  return root;
}

