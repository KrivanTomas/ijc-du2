#include "libhtab-impl.h"
#include <string.h>

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    
    size_t index = htab_hash_function(key) % t->arr_size;

    for(struct htab_item *item = t->table[index]; item != NULL; item = item->next) {
        if(strcmp(item->pair.key, key) == 0) return &item->pair;
    }

    return NULL;
}   
