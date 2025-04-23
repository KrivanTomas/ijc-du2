# Makefile
# Řešení IJC-DU2 24.4.2025
# Autor: Tomáš Křivan, FIT

CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -O2
CFLAGS += -fpic
#CFLAGS += -g

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

check: all
	echo "Lorem ipsum dolor sit amet,\nconsectetur adipiscing elit.\nProin eu mollis mauris.\nAliquam maximus iaculis augue.\nSuspendisse erat magna,\nfeugiat sed accumsan eu,\ntincidunt quis elit." | ./tail -n 3
	echo "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin eu mollis mauris. Aliquam maximus iaculis augue. Suspendisse erat magna, feugiat sed accumsan eu, tincidunt quis elit. Etiam aliquet felis sapien, ut elementum mauris ultricies a. Donec pharetra, lorem ac sodales gravida, leo orci luctus dui, at consequat orci neque sed ligula. Pellentesque non tellus vitae nisl sodales faucibus nec eget erat. Nullam nec ipsum diam. Donec eleifend felis elementum ex laoreet gravida. Nullam eu tempus massa. Integer viverra, leo et porta posuere, arcu mi sagittis risus, a facilisis velit velit at enim. Nunc sodales venenatis libero sed fringilla. Vestibulum sed velit scelerisque, aliquam dolor quis, volutpat neque. Vestibulum dignissim in elit quis gravida. In luctus, quam a imperdiet bibendum, arcu erat fringilla ante, nec consequat mi eros vel purus. Donec in justo aliquam, porttitor odio non, semper elit." | ./maxwordcount
	export LD_LIBRARY_PATH="."; echo "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin eu mollis mauris. Aliquam maximus iaculis augue. Suspendisse erat magna, feugiat sed accumsan eu, tincidunt quis elit. Etiam aliquet felis sapien, ut elementum mauris ultricies a. Donec pharetra, lorem ac sodales gravida, leo orci luctus dui, at consequat orci neque sed ligula. Pellentesque non tellus vitae nisl sodales faucibus nec eget erat. Nullam nec ipsum diam. Donec eleifend felis elementum ex laoreet gravida. Nullam eu tempus massa. Integer viverra, leo et porta posuere, arcu mi sagittis risus, a facilisis velit velit at enim. Nunc sodales venenatis libero sed fringilla. Vestibulum sed velit scelerisque, aliquam dolor quis, volutpat neque. Vestibulum dignissim in elit quis gravida. In luctus, quam a imperdiet bibendum, arcu erat fringilla ante, nec consequat mi eros vel purus. Donec in justo aliquam, porttitor odio non, semper elit." | ./maxwordcount-dynamic
	echo "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin eu mollis mauris. Aliquam maximus iaculis augue. Suspendisse erat magna, feugiat sed accumsan eu, tincidunt quis elit. Etiam aliquet felis sapien, ut elementum mauris ultricies a. Donec pharetra, lorem ac sodales gravida, leo orci luctus dui, at consequat orci neque sed ligula. Pellentesque non tellus vitae nisl sodales faucibus nec eget erat. Nullam nec ipsum diam. Donec eleifend felis elementum ex laoreet gravida. Nullam eu tempus massa. Integer viverra, leo et porta posuere, arcu mi sagittis risus, a facilisis velit velit at enim. Nunc sodales venenatis libero sed fringilla. Vestibulum sed velit scelerisque, aliquam dolor quis, volutpat neque. Vestibulum dignissim in elit quis gravida. In luctus, quam a imperdiet bibendum, arcu erat fringilla ante, nec consequat mi eros vel purus. Donec in justo aliquam, porttitor odio non, semper elit." | ./maxwordcount-cpp

.PHONY: pack
pack:
	zip xkrivat00.zip *.c *.cc *.h Makefile

.PHONY: clean
clean:
	rm *.o tail maxwordcount maxwordcount-cpp libhtab.a libhtab.so
