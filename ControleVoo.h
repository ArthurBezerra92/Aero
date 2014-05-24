#ifndef CONTROLEVOO_H_INCLUDED
#define CONTROLEVOO_H_INCLUDED
#include "Voo.h"
#include "VooEmpresa.h"

void enter(), search(), save();
void display(Voo *info);
void load(), list();
void delete(Voo **, Voo **);
Voo *find(char*);

void dsl_store(Voo *i, Voo **start,Voo **last);
void dsl_storeQtde(VooEmpresa *i,VooEmpresa **start,VooEmpresa **last);
void qtdeVooEmp(char *empresa);
void qtdeVoos();

#endif // CONTROLEVOO_H_INCLUDED
