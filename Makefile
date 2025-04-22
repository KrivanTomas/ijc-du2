CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra
CFLAGS += -fpic
CFLAGS += -O2

CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -O2

HTAB_SOURCE = $(wildcard htab_*.c)
HTAB_OBJ = $(patsubst %.c, %.o, $(HTAB_SOURCE))

.PHONY: all
all: tail maxwordcount maxwordcount-dynamic maxwordcount-cpp

tail: tail.c
	$(CC) $(CFLAGS) $^ -o $@

maxwordcount: maxwordcount.o io.o libhtab.a
	$(CC) $(CFLAGS) -static maxwordcount.o io.o -o $@ -L. -lhtab

maxwordcount-dynamic: maxwordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) maxwordcount.o io.o -o $@ -L. -lhtab

maxwordcount-cpp: maxwordcount-cpp.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

libhtab.a: $(HTAB_OBJ)
	ar rcs $@ $^

libhtab.so: $(HTAB_OBJ)
	$(CC) $(CFLAGS) -shared $^ -o $@

.PHONY: pack
pack:
	zip xkrivat00.zip *.c *.cc *.h Makefile

.PHONY: clean
clean:
	rm *.o tail maxwordcount maxwordcount-cpp libhtab.a libhtab.so
