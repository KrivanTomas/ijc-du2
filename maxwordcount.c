#include <stdio.h>
#include <stdlib.h>
#include "htab.h"

#define MAX_WORD_LEN 1000


int read_word(unsigned max, char s[max], FILE *f);
void print_pair(htab_pair_t *pair);

htab_pair_t *max_pair = NULL;
void find_max(htab_pair_t *pair) {
    if(max_pair == NULL || pair->value > max_pair->value){
        max_pair = pair; 
    }
}

int main() {
    htab_t *map = htab_init(1000);
    
    char *buffer = malloc(MAX_WORD_LEN * sizeof(char));
    
    while(read_word(MAX_WORD_LEN, buffer, stdin) != EOF) {
        htab_pair_t *pair = htab_lookup_add(map, buffer);
        pair->value++;
        pair = htab_find(map, buffer);
    }

    //htab_for_each(map, print_pair);
    htab_for_each(map, find_max);
    printf("%s\t%u\n", max_pair->key, max_pair->value);

    htab_free(map);

    return 0;
}


void print_pair(htab_pair_t *pair) {
    printf("%s: %u\n", pair->key, pair->value);
}

