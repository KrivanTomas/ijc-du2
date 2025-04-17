CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra

CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -O2

HTAB_SOURCE = $(wildcard htab_*.c)
HTAB_OBJ = $(patsubst %.c, %.o, $(HTAB_SOURCE))

.PHONY: all
all: tail maxwordcount maxwordcount-cpp


tail: tail.c
	$(CC) $(CFLAGS) $^ -o $@

maxwordcount: maxwordcount.c io.c libhtab.a
	$(CC) $(CFLAGS) $^ -o $@ 

maxwordcount-cpp: maxwordcount-cpp.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

libhtab.a: $(HTAB_OBJ)
	ar rcs $@ $^

libhtab.so: $(HTAB_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: pack
pack:
	zip xkrivat00.zip *.c *.cc *.h Makefile

.PHONY: clean
clean:
	rm *.o tail maxwordcount maxwordcount-cpp libhtab.a libhtab.so
