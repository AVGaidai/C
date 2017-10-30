P=main.out
OBJECTS=main.c
CFLAGS=-Wall -g -pedantic -ansi
LIBS=-lpanel -lncurses
CC=gcc

all:
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LIBS)

clean:
	rm -rf *.out
