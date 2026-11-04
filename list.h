#ifndef LIST_H 
#define LIST_H 

// Dans list.h
typedef struct { // On définit un nouveau type composé
int* data; // le tableau, alloué sur le tas
int size; // nombre d'éléments réellement présents
int capacity; // nombre de cases allouées (size <= capacity)
} List;

List* list_create();
void list_free(List* l);
void list_print(const List* l);
int list_get(const List* l, int index);
void list_set(List* l, int index, int value);
void list_add(List* l, int value);
int list_pop(List* l);
void list_remove(List* l, int index);
void list_clear(List* l);

#endif