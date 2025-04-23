// io.c
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "io.h"

int read_word(unsigned max, char s[max], FILE *f) {
    static bool length_warning = false;
    int ch;
    size_t counter = 0;
    bool word_started = false;
    while((ch = getc(f)) != EOF) {
        if(isspace(ch)) {
            if(!word_started) continue;
            s[counter] = '\0';
            return counter;
        }
        else s[counter++] = ch;
        word_started = true;

        if(counter == max - 1) {
            if(!length_warning){
                length_warning = true;
                s[counter] = '\0';
                fprintf(stderr, "Warning: word shortened to max length of %u\n", max);
                return counter;
            }
        }
    }
    return EOF;
}
