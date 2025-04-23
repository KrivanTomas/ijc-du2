// htab_erase.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#include "libhtab-impl.h"
#include <stdlib.h>
#include <string.h>

bool htab_erase(htab_t *t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    
    struct htab_item **prev_ptr = &t->table[index];
    for(struct htab_item *item = t->table[index]; item != NULL; item = item->next) {
        if(strcmp(item->pair.key, key) == 0) {
            *prev_ptr = item->next;
            free(item);
            return true;
        }
        prev_ptr = &item->next;
    }
    return false;
}
