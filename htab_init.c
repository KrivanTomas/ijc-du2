#include "libhtab-impl.h"
#include <stdlib.h>

htab_t *htab_init(size_t n) {
    htab_t *map;

    map = calloc(sizeof(htab_t) + n * sizeof(size_t), 1);

    if(map == NULL) return NULL;

    map->arr_size = n;
    map->size = 0;
    
    return map;
}
