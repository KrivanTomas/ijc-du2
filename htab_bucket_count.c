#include "libhtab-impl.h"

size_t htab_bucket_count(const htab_t *t) {
    return t->size;
}
