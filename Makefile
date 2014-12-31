CC=cc
CFLAGS=-c -Wall

all: SortingAlgorithms

SortingAlgorithms: Algoritmos.o Interfaz.o Principal.o
	$(CC) Principal.o Algoritmos.o Interfaz.o -lncurses -o SortingAlgorithms

Principal.o: Principal.c
	$(CC) $(CFLAGS) Principal.c

Algoritmos.o: Algoritmos.c
	$(CC) $(CFLAGS) Algoritmos.c

Interfaz.o: Interfaz.c
	$(CC) $(CFLAGS) Interfaz.c

clean:
	rm -rf *o SortingAlgorithms

