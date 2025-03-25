#include <stdio.h>
#include <string.h>

#define LINE_LIMIT 4095
#define DEFAULT_LINE_COUNT 10

void print_tail(FILE *stream, int count);

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
            if(filename_position == -1) {
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
        if(source == NULL) return 1;
    }

    // Line count
    count = count != -1 ? count : DEFAULT_LINE_COUNT;

    print_tail(source, count);
}

void print_tail(FILE *stream, int count) {
    printf("%d\n", count);
}