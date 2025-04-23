// maxwordcount.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

void find_max(htab_pair_t *pair);
void print_max_pairs(htab_pair_t *pair);

size_t max_count = 0;

int main() {
    // buffer output by blocks for faster output (for inputs with a lot of 'max_count' words)
    setvbuf(stdout, NULL, _IOFBF, 4096);

    // Space / Time complexity tradeof
    // 300k * sizeof(ptr)B = 2.4 MB (bucket array only)
    //
    // Larger values mean less collision and less searching
    // through linked lists yielding faster speeds for searching
    //
    // There are ~470,000 words in the English dictionary times the
    // many variations ("end", "End", "END", "end?", "end.", "end!" ...) that are
    // recognised as different words by this program
    //
    // -> 300000 (2.4MB + list) is almost nothing on modern computers, while
    // being plenty fast with the input I am testing it with.
    htab_t *map = htab_init(300000);
    
    char *buffer = malloc(MAX_WORD_LEN * sizeof(char));
    
    while(read_word(MAX_WORD_LEN, buffer, stdin) != EOF) {
        htab_pair_t *pair = htab_lookup_add(map, buffer);
        pair->value++;
        pair = htab_find(map, buffer);
    }

    htab_for_each(map, find_max);
    htab_for_each(map, print_max_pairs);

    fflush(stdout);

    htab_free(map);

    return 0;
}

void find_max(htab_pair_t *pair) {
    max_count = pair->value > max_count ? pair->value : max_count;
}

void print_max_pairs(htab_pair_t *pair) {
    if(pair->value == max_count)
        printf("%s\t%u\n", pair->key, pair->value);
}  

