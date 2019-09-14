P=main.out
Q=../queue/queue.c ../queue/queue.h
L=../queue/singly_linked_list/sllist.c ../queue/singly_linked_list/sllist.h
OBJ=main.c $(Q) $(L)
CC=gcc
CFLAGS=-Wall -g -pedantic -ansi
LDLIBS=-lm

all:
	$(CC) $(CFLAGS) -o $(P) $(OBJ) $(LDLIBS)

clean:
	rm -rf *.out *.txt
