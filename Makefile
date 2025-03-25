CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra

.PHONY: all
all: tail


tail: tail.c
	$(CC) $(CFLAGS) $^ -o tail



.PHONY: clean
clean:
	rm tail