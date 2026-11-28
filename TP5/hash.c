#include <stdlib.h>
#include <stdio.h>
#include "strings.h"
#include "hash.h"


unsigned int hash_string(const char* key) {
    if (key == NULL)
    {
        fprintf(stderr, "Error: the key cannot be NULL");
        exit(1);
    }
    
    unsigned int hash = 0;
    while (*key != '\0') {
        hash = hash * 33 + (unsigned char)*key;
        key++;
    }

    return hash;
}


Entry* create_entry(const char* key, int value) {
    if (key == NULL)
    {
        fprintf(stderr, "Error: the key cannot be NULL");
        exit(1);
    }
    
    if (value < 0)
    {
        fprintf(stderr, "Error: the value  cannot be negative");
        exit(1);
    }

    Entry* entry = malloc(sizeof (Entry));
    if (entry == NULL)
    {
        fprintf(stderr, "Error: failed to allocate memory for Entry\n");
        exit(1);
    }

    entry->key = str_dup(key);
    if (entry->key == NULL)
    {
        fprintf(stderr, "Error: failed to duplicate value\n");
        exit(1);
    } 
    
    entry->value = value;
    return entry;   
}

void free_entry(Entry* entry) {
    if (entry == NULL)
    {
        return;
    }
    
    free(entry->key);
    free(entry);
}


HashMap* map_create(int capacity) {
    if (capacity <= 0)
    {
        fprintf(stderr, "Error: the capacity should be positive");
        exit(1);
    }    

    HashMap* map = malloc(sizeof(HashMap));
    if (map == NULL)
    {
        fprintf(stderr, "Error: failed to allocate memory for HashMap\n");
        exit(1);
    }

    Entry** entryArray = malloc(capacity * sizeof(Entry*));
    if (entryArray == NULL)
    {
        fprintf(stderr, "Error: failed to allocate memory for entryArray\n");
        free(map);
        exit(1);
    }
    
    
    map->entries = entryArray;
    for (int i = 0; i < capacity ; i++)
    {
        entryArray[i] = NULL;
    }
    
    map->capacity = capacity;

    return map;
}

void map_put(HashMap* map, const char* key, int value) {
    if (map == NULL)
    {
        fprintf(stderr, "Error: map cannot be NULL");
        exit(1);
    }
    

    if (key == NULL)
    {
        fprintf(stderr, "Error: the key cannot be NULL");
        exit(1);
    }
    
    if (value < 0)
    {
        fprintf(stderr, "Error: the value cannot be negative");
        exit(1);
    }

    unsigned int hashCase = hash_string(key) % map->capacity;

    if (map->entries[hashCase] != NULL)
    {
        free_entry(map->entries[hashCase]);
    }

    map->entries[hashCase] = create_entry(key, value);
}

int* map_get(const HashMap* map, const char* key) {
    if (map == NULL)
    {
        fprintf(stderr, "Error: map cannot be NULL");
        exit(1);
    }
    
    if (key == NULL)
    {
        fprintf(stderr, "Error: the key cannot be NULL");
        exit(1);
    }

    unsigned int hashCase = hash_string(key) % map->capacity;

    if (map->entries[hashCase] == NULL) {
        return NULL;
    }

    return &map->entries[hashCase]->value;
    
}
void map_print(const HashMap* map) {
    char* key = "";
    int value = 0;
    for (int i = 0; i < map->capacity; i++) {
        if (map->entries[i] != NULL) {
            key = map->entries[i]->key;
            value = map->entries[i]->value;
            printf("[%d] %s:%d\n", i, key, value);
        }
    }

    return;
}

void map_free(HashMap* map)
{
    if (map == NULL)
        return;

    for (int i = 0; i < map->capacity; i++)
    {
        if (map->entries[i] != NULL)
        {
            free_entry(map->entries[i]);
        }
    }

    free(map->entries);
    free(map);
}