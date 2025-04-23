// htab_hash_function.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#include "libhtab-impl.h"
#include <stdint.h>

size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}

