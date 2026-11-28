#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "stack.h"


Scope* scope_push(Scope* parent)
{
    Scope* scope = malloc(sizeof(Scope));

    if (scope == NULL)
        return NULL;

    scope->vars = map_create(8);
    scope->parent = parent;

    return scope;
}

Scope* scope_pop(Scope* top) {
    if (top == NULL)
    {
        fprintf(stderr, "Error: Scope cannot be NULL.\n");
        exit(1);
    }

    Scope* parent = top->parent;
    map_free(top->vars);
    free(top);
    return parent;
}

void scope_declare(Scope* top, const char* name, int value) {
    if (top == NULL)
    {
        fprintf(stderr, "Error: Scope cannot be NULL.\n");
        exit(1);
    }

    if (name == NULL)
    {
        fprintf(stderr, "Error: Invalid name.\n");
        exit(1);
    }

    map_put(top->vars,name, value);

}

int* scope_get(Scope* top, const char* name) {

    if (top == NULL)
    {
        fprintf(stderr, "Error: Scope cannot be NULL.\n");
        exit(1);
    }

    if (name == NULL)
    {
        fprintf(stderr, "Error: Invalid name.\n");
        exit(1);
    }
    Scope* current = top;
    while (current != NULL)
    {
        int* result = map_get(current->vars, name);
        if (result != NULL) {
            return result;
        } else {
            current = current->parent;
        }
    }
    return NULL;
    
}

Scope* buy(Scope* top, int price) {
    
    Scope* local = scope_push(top);
    
    scope_declare(local, "price", price);
    scope_declare(local, "tax", 2);

    int* tax = scope_get(local, "tax");
    if (tax == NULL)
    {
        fprintf(stderr, "Error: Tax cannot be NULL.\n");
        exit(1);
    }
    int* total = scope_get(local, "total");
    if (total == NULL)
    {
        fprintf(stderr, "Error: Total cannot be NULL.\n");
        exit(1);
    }

    
    *total = *total + price + *tax;
    local = scope_pop(local);

    return local;

}
