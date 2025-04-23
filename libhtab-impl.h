// libhtab-impl.h
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#ifndef HTAB_IMPL_H_
#define HTAB_IMPL_H_

#include "htab.h"

struct htab_item {
    struct htab_item *next;
    struct htab_pair pair;
};

struct htab {
   size_t size;
   size_t arr_size;
   struct htab_item *table[];
};

#endif
