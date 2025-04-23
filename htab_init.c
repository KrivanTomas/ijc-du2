// htab_init.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

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
