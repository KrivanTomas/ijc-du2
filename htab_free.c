// htab_free.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#include "libhtab-impl.h"
#include <stdlib.h>

void htab_free(htab_t *t) {
    htab_clear(t);
    free(t);
}
