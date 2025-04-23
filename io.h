// io.h
// Řešení IJC-DU2, příklad 2), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0

#ifndef IO_H_
#define IO_H_

#include <stdio.h>

#define MAX_WORD_LEN 1000

int read_word(unsigned max, char s[max], FILE *f);

#endif
