#ifndef HASH_H 
#define HASH_H 

typedef struct {
    char* key; // le nom de la variable
    int value; // sa valeur
} Entry;

typedef struct {
    Entry** entries; // le tableau qui accueil les variables : chacune contient l'adresse d'une entrée (NULL
    int capacity;
} HashMap;

unsigned int hash_string(const char* key);
Entry* create_entry(const char* key, int value);
void free_entry(Entry* entry);
HashMap* map_create(int capacity);
void map_put(HashMap* map, const char* key, int value);
int* map_get(const HashMap* map, const char* key);
void map_print(const HashMap* map);
void map_free(HashMap* map);



#endif