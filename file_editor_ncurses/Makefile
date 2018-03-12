P=main.out
FM=file_manager.c file_manager.h
RK=readkey.c readkey.h
SLL=singly_linked_list/sllist.c singly_linked_list/sllist.h
OBJECTS=main.c $(FM) $(RK) $(SLL)
CFLAGS=-Wall -g -pedantic -ansi
LIBS=-lpanel -lncurses
CC=gcc

all:
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LIBS)

clean:
	rm -rf *.out
