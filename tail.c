#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    if(argc > 4) { // too many arguments
        return 1;       
    }

    int count = -1;
    int filename_position = -1;

    // Scan for line count arguments
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-n") == 0) {
            if(i + 1 >= argc) {
                return 1;
            }
            count = atoi(argv[i+1]);
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
            perror("Could not open source file");
            return 1;
        }
    }

    // Line count
    count = count != -1 ? count : DEFAULT_LINE_COUNT;

    print_tail(source, count);
}

void print_tail(FILE *stream, unsigned int count) {
    cbuffer_t *cbuffer = cbuf_create(count);
    char *line_buffer = malloc(LINE_LIMIT * sizeof(char));
    
    while(fgets(line_buffer, LINE_LIMIT, stream) != NULL) {
        cbuf_put(cbuffer, line_buffer);
    }
    free(line_buffer);
    char *line = NULL;
    while((line = cbuf_get(cbuffer)) != NULL) {
        printf("%s", line);
    }   
    cbuf_free(cbuffer);
}

cbuffer_t *cbuf_create(unsigned int n) {  
    if(n == 0) return NULL;

    cbuffer_t *cbuff = malloc(sizeof(cbuffer_t) + (n + 1) * sizeof(char) * LINE_LIMIT);
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
    strncpy(&cb->buffer[cb->write_head++ * LINE_LIMIT], line, LINE_LIMIT);
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
