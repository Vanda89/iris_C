#include <stdlib.h>
#include <stdio.h>
#include "list.h"

List* list_create() {
    List* list = malloc(sizeof(List));

    if(list == NULL) {
        return NULL;
    }

    list->size = 0;
    list->capacity = 12;
    list->data = malloc(list->capacity * sizeof(int));

    if (list->data == NULL)
    {
        free(list);
        return NULL;
    }

    return list;
};

void list_free(List* l){
    if (l == NULL)
    {
        return;
    }
    free(l->data);
    free(l);
} ;

void list_print(const List* l) {
    int i = 0;
    if (l == NULL)
    {
        return;
    }
    while (i < l->size)
    {
        printf("%d \n", l->data[i]);
        i++;
    }    
};

int list_get(const List* l, int index) {
    if (l->data == NULL)
    {
        return -1;
    }

    if (index <= 0 || index > l->size)
    {
        return -1;
    }

    return l->data[index];
};

void list_set(List* l, int index, int value){
    if (l->data == NULL)
    {
        return ;
    }

    if (index < 0 || index > l->size)
    {
        return;
    }

    l->data[index] = value;
};

void list_add(List* l, int value) {
    if (l->data == NULL)
    {
        return ;
    }

    int new_capacity = l->capacity * 2;
    int* new_data = malloc(new_capacity * sizeof(int));
    int i = 0;
    
    if (new_data == NULL)
    {
        return;
    }
    
    while (i < l->size) {
        new_data[i] = l->data[i];
        i++;
    }

    free(l->data);
    l->data = new_data;
    l->capacity = new_capacity;

    l->data[l->size] = value;
    l->size++;

};

int list_pop(List* l) {
    if (l->data == NULL)
    {
        return -1;
    }

    if (l->size <= 0)
    {
        return -1;
    }

    int last_value = l->data[l->size -1];
    l->size--;
    return last_value;
    
};

void list_remove(List* l, int index) {
    int i = index;
     if (l->data == NULL)
    {
        return ;
    }

    if (index < 0 || index > l->size)
    {
        return;
    }

    while (i< l->size -1)
    {
        l->data[i] = l->data[i + 1];
        i++;
    }
    l->size--;
    
};

void list_clear(List* l) {
    if (l == NULL)
    {
        return ;
    }
    l->size =0;
};







