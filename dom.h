#ifndef DOM_H 
#define DOM_H 


typedef struct Element {
    char* tag;
    char* id;
    char* text;
    struct Element** children;
    int nb_children;
    int capacity;
} Element;

Element* create_element(const char* tag, const char* id, const char* text);
void append_child(Element* parent, Element* child);
int count_elements(const Element* e);
int count_by_tag(const Element* e, const char* tag);
int dom_height(const Element* e);
Element* find_by_id(Element* e, const char* id);
int depth_of(const Element* e, const char* id);
void render(const Element* e, int depth);
void free_element(Element* e);

#endif