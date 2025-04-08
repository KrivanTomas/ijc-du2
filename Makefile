CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra

CXX = g++
CXXFLAGS = -std=c++17 -pedantic -Wall -O2

.PHONY: all
all: tail maxwordcount maxwordcount-cpp


tail: tail.c
	$(CC) $(CFLAGS) $^ -o $@

maxwordcount: maxwordcount.c libhtab.a
	$(CC) $(CFLAGS) $^ -o $@

maxwordcount-cpp: maxwordcount-cpp.cc
	$(CXX) $(CXXFLAGS) $^ -o $@

libhtab.a: libhtab.c
	ar rcs $@ $^

libhtab.so: libhtab.c
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm tail maxwordcount maxwordcount-cpp
