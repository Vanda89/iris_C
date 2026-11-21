#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "dom.h"

#define MIN_CHILDREN 4

Element* create_element(const char* tag, const char* id, const char* text) {
    
    if (tag == NULL) {
        fprintf(stderr, "Failed to create Element : an element must have a tag\n");
        exit(1);
    }
    
    Element* element = malloc(sizeof(Element));
    if (element == NULL) {
        fprintf(stderr, "Failed to allocate memory for Element\n");
        exit(1);
    }

    element->tag = tag != NULL ? str_dup(tag) : NULL;
    element->id = id != NULL ? str_dup(id) : NULL;
    element->text = text != NULL ? str_dup(text) : NULL;
    element->capacity= MIN_CHILDREN;
    element->nb_children= 0;
    
    element->children = malloc(element->capacity * sizeof(Element*));
    if (element->children == NULL){
        fprintf(stderr, "Failed to allocate memory for Element's children\n");
        exit(1);
    }
    
    return element;
}

void append_child(Element* parent, Element* child) {
    if(child == NULL) {
        fprintf(stderr, "Error: child is NULL\n");
        exit(1);
    }
    if(parent == NULL) {
        fprintf(stderr, "Error: parent is NULL\n");
        exit(1);
    }
    if (parent->nb_children == parent->capacity)
    {
        parent->capacity = parent->capacity * 2;
        Element** tmpArray = realloc(parent->children, parent->capacity * sizeof(Element*));
        if (tmpArray == NULL)
        {
            fprintf(stderr, "Failed to reallocate memory in tmpArray\n");
            exit(1);
        }
        parent->children = tmpArray;
    }

    parent->children[parent->nb_children] = child;
    parent->nb_children++;
}

int count_elements(const Element* e) {
    if (e->nb_children == 0) {
        return 1;
    } 
    int counter = 1;

    for (int i = 0; i < e->nb_children; i++) {
        counter = counter + count_elements(e->children[i]);
    }
    return counter;
}

int count_by_tag(const Element* e, const char* tag) {
    int counter = 0;
    if(str_equals(e->tag, tag)) {
        counter++;
    } 
    for (int i = 0; i < e->nb_children; i++) {
        
        counter = counter + count_by_tag(e->children[i], tag);
       
    }
    return counter;
} 

int dom_height(const Element* e) {
    int height = 0;
    if(e->nb_children == 0) {
        height++;
    } 

    int max_height = 0;
    
    for (int i = 0; i < e->nb_children; i++) {
        int child_height = dom_height(e->children[i]);
        if (child_height > max_height) {
            max_height = child_height;
        }
    }
    //enfant avec le plus d'enfants + parent de l'enfant
    height = max_height + 1;

    return height;
}

Element* find_by_id(Element* e, const char* id) {

    if (e->id != NULL && str_equals(e->id, id)) {
        return e;
    }
    
    for (int i = 0; i < e->nb_children; i++) {
        Element* goodElement = find_by_id(e->children[i], id);

        if (goodElement != NULL) {
            return goodElement;
        }
    }
    return NULL;

}

int depth_of(const Element* e, const char* id) {

    if (e->id != NULL && str_equals(e->id, id)) {
        return 0;
    }

    for (int i = 0; i < e->nb_children; i++) {
        int child_depth = depth_of(e->children[i], id);
        if (child_depth > -1) {
            return child_depth + 1;
        }
    }
    
    return -1;
}

void print_indent(int depth) {
    for (int i = 0; i < depth*2; i++) {
        printf(" ");
    }
}

void render(const Element* e, int depth) {
    if (e == NULL){
        return;
    }
     
    print_indent(depth);    

    if(e->id!=NULL) printf("<%s id=\"%s\">\n",e->tag, e->id);
    else printf("<%s>\n",e->tag);
    
    if(e->text != NULL){
        print_indent(depth+1);
        printf("%s\n",e->text);
    } 

    for (int i = 0; i < e->nb_children; i++) {
        render(e->children[i], depth + 1);
    }
    
    print_indent(depth);
    printf("</%s>\n",e->tag);
}


void free_element(Element* e) {
    if (e == NULL){
        return;
    }

    for (int i = 0; i < e->nb_children; i++) {
     
        free_element(e->children[i]);
    }

    free(e->tag);
    free(e->id);
    free(e->text);
    free(e->children);
    free(e);
}
