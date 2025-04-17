#include "libhtab-impl.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    size_t found_count = 0;
    for(size_t bucket_index = 0; bucket_index < t->arr_size; bucket_index++) {
        for(struct htab_item *item = t->table[bucket_index]; item != NULL; item = item->next){
            found_count++;
            f(&item->pair);
        }
        if(found_count == t->size) return;
    }
}
