// htab_lookup_add.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#include "libhtab-impl.h"
#include <stdlib.h>


htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    
    htab_pair_t *found_pair = htab_find(t, key);
    if(found_pair != NULL) return found_pair;

    struct htab_item *new_item = malloc(sizeof(struct htab_item));
    if(new_item == NULL) return NULL;


    char *key_copy = malloc(strlen(key) + 1);

    strcpy(key_copy, key);
    new_item->pair.key = key_copy;
    new_item->pair.value = 0;

    if(new_item->pair.key == NULL) {
        free(new_item);
        return NULL;
    }

    
    size_t index = htab_hash_function(key) % t->arr_size;

    new_item->next = t->table[index];
    t->table[index] = new_item;
    t->size++;
    return &new_item->pair;
}
