
#ifndef STACK_H 
#define STACK_H 
#include "hash.h"

typedef struct Scope {
HashMap* vars; // les variables de cette portée
struct Scope* parent; // la portée du dessous (NULL pour la portée globale)
} Scope;

Scope* scope_push(Scope* parent);
Scope* scope_pop(Scope* top);
void scope_declare(Scope* top, const char* name, int value);
int* scope_get(Scope* top, const char* name);
Scope* buy(Scope* top, int price); 
#endif