P=main.out
OBJECTS=main.c file_manager.c file_manager.h
CFLAGS=-Wall -g -pedantic -ansi
LIBS=-lpanel -lncurses
CC=gcc

all:
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LIBS)

clean:
	rm -rf *.out
