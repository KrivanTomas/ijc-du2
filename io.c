#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool length_warning = false;

int read_word(unsigned max, char s[max], FILE *f) {
    int ch;
    size_t counter = 0;
    bool word_started = false;
    while((ch = fgetc(f)) != EOF) {
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
