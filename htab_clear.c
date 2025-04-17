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
