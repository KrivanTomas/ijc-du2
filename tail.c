// tail.c
// Řešení IJC-DU2, příklad 1), 24.4.2025
// Autor: Tomáš Křivan, FIT
// Přeloženo: gcc 11.4.0
// Implementace POSIX tail pomocí C11

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LINE_LIMIT 4095
#define DEFAULT_LINE_COUNT 10


typedef struct Cbuffer {
    unsigned int length;
    unsigned int read_head;
    unsigned int write_head;
    char buffer[];
} cbuffer_t;


cbuffer_t *cbuf_create(unsigned int n);
void cbuf_put(cbuffer_t *cb, char *line);
char *cbuf_get(cbuffer_t *cb);
void cbuf_free(cbuffer_t *cb);

void print_tail(FILE *stream, unsigned int count);

int main(int argc, char **argv) {
    if(argc > 4) {
        fprintf(stderr, "Too many arguments\n");
        return 1;       
    }

    int count = -1;
    int filename_position = -1;

    // Scan for line count argument (-n N)
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-n") == 0) {
            if(i + 1 >= argc) {
                return 1;
            }
            count = atoi(argv[i+1]);
            if(count < 0) {
                fprintf(stderr, "Parameter '-n' supports positive values only");
                return 1;
            }
            if(filename_position == -1 && i + 3 <= argc) {
                filename_position = i + 2;
            }
            break;
        }
        filename_position = i;
    }


    // Source file
    FILE *source = stdin;
    if(filename_position != -1) {
        source = fopen(argv[filename_position], "r");
        if(source == NULL) {
            perror("fopen");
            return 1;
        }
    }

    // Line count
    count = count != -1 ? count : DEFAULT_LINE_COUNT;

    print_tail(source, count);
    fclose(source);
}

void print_tail(FILE *stream, unsigned int count) {
    bool lenght_warning = false;
    cbuffer_t *cbuffer = cbuf_create(count);
    if(cbuffer == NULL) return; 
    char *line_buffer = malloc(LINE_LIMIT * sizeof(char));
    if(line_buffer == NULL) {
        cbuf_free(cbuffer);
        perror("malloc");
        return;
    }
    
    // Read lines
    while(fgets(line_buffer, LINE_LIMIT, stream) != NULL) {
        cbuf_put(cbuffer, line_buffer);
        size_t len = strlen(line_buffer);
        if(line_buffer[len-1] != '\n' && line_buffer[len-1] != EOF) {
            if(!lenght_warning) {
                fprintf(stderr, "Warning: input lines are longer than %d, resulting lines may be cut\n", LINE_LIMIT - 1);
                lenght_warning = true;
            }
            int ch;
            // flush remaining characters
            while((ch = fgetc(stream)) != '\n' && ch != EOF) ;
        }
    }

    free(line_buffer);

    char *line = NULL;
    // Print last n lines
    while((line = cbuf_get(cbuffer)) != NULL) {
        printf("%s", line);
    }   

    cbuf_free(cbuffer);
}

cbuffer_t *cbuf_create(unsigned int n) {  
    if(n == 0) return NULL;

    cbuffer_t *cbuff = malloc(sizeof(cbuffer_t) + (n + 1) * sizeof(char) * LINE_LIMIT);
    if(cbuff == NULL) {
        perror("malloc");
        return NULL;
    }
    cbuff->read_head = 0;
    cbuff->write_head = 0;
    cbuff->length = n;

    return cbuff;
}

void cbuf_put(cbuffer_t *cb, char *line) {
    if(cb == NULL) return;

    if((cb->write_head + 1) % (cb->length + 1) == cb->read_head) {
        cb->read_head++;
        cb->read_head = cb->read_head % (cb->length + 1);
    }
    size_t len = strlen(line);
    strncpy(&cb->buffer[cb->write_head * LINE_LIMIT], line, LINE_LIMIT);

    // add newline to cut lines and fix strncpy not putting '\0' in strings that dont reach LINE_LIMIT
    cb->buffer[cb->write_head * LINE_LIMIT + LINE_LIMIT - 2] = '\n';
    cb->buffer[cb->write_head * LINE_LIMIT + len] = '\0';

    cb->write_head++;
    cb->write_head = cb->write_head % (cb->length + 1);
}

char *cbuf_get(cbuffer_t *cb) {
    if(cb == NULL) return NULL;
    
    if(cb->read_head == cb->write_head)
        return NULL;
    char *line = &cb->buffer[cb->read_head++ * LINE_LIMIT];
    cb->read_head = cb->read_head % (cb->length + 1);
    return line;
}

void cbuf_free(cbuffer_t *cb) {
    free(cb);
}
