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
