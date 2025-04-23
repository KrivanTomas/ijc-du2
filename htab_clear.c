// htab_clear.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#include "libhtab-impl.h"
#include <stdlib.h>

void htab_clear(htab_t *t) {
    for(size_t bucket_index = 0; bucket_index < t->arr_size; bucket_index++) {
        for(struct htab_item *item = t->table[bucket_index]; item != NULL; ){
            struct htab_item *temp = item;
            item = item->next;
            free(temp);
        }
        t->table[bucket_index] = NULL;
    }
}
