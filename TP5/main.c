#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "hash.h"
#include "stack.h"




int main(void) {


printf("----------------------------\n");
printf("hello = %d\n",hash_string("hello"));
printf("case %d\n", hash_string("hello") % 8);

printf("price = %d\n",hash_string("price"));
printf("case %d\n", hash_string("price") % 8);

printf("total = %d\n",hash_string("total"));
printf("case %d\n", hash_string("total") % 8);

printf("tax = %d\n",hash_string("tax"));
printf("case %d\n", hash_string("tax") % 8);

Entry* price = create_entry("price", 12);
Entry* total = create_entry("total", 0);
Entry* tax = create_entry("tax", 2);

HashMap* map = map_create(8);
map_put(map, price->key, price->value);         
map_put(map, total->key, total->value);         
map_put(map, tax->key, tax->value);         

int* priceAdress = map_get(map, price->key);
printf("Valeur de price : %d\n", *priceAdress);

map_print(map);


printf("----------------------------\n");

Scope* global = scope_push(NULL);
Scope* firstScope = scope_push(global);
map_put(global->vars, price->key, price->value);         
map_put(global->vars, total->key, total->value);         
map_put(firstScope->vars, tax->key, tax->value); 
printf("global vars children\n");
map_print(global->vars);

printf("firstScope vars children\n");
map_print(firstScope->vars);

printf("----------------------------\n");

printf("global: %p\n", global);
printf("firstScope: %p\n", firstScope);
printf("firstScope parent: %p\n", firstScope->parent);

Scope* newTop = scope_pop(firstScope);
printf("Le parent est %p\n", (void*)newTop);
scope_declare(global, "Hello World !", 12);
map_print(global->vars);
int* result = scope_get(global, "price");
printf("Price adress : %d \n", *result);




global = buy(global, 5);
int* totalResult = scope_get(global, "total");
printf("Total : %d\n", *totalResult);
int* priceResult = scope_get(global, "price");
printf("Price : %d\n", *priceResult);

global = buy(global, 10);

totalResult = scope_get(global, "total");
printf("Total après 2eme achat : %d\n", *totalResult);

scope_declare(global, "x", 3);
scope_declare(global, "y", 4);
scope_declare(global, "i", 0);
map_print(global->vars);



free_entry(price);
free_entry(total);
free_entry(tax);
map_free(map);

scope_pop(global);

return 0;
}