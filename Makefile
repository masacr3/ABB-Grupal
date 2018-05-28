EXEC=abb
cc=gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
CFILES=testing.c abb.c pruebas_catedra.c main.c pila.c
HFILES=abb.h pila.h testing.h

all:
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC)
run: all
	./$(EXEC)
valgrind: all
	valgrind $(VFLAGS) ./$(EXEC)
