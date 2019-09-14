P=main.out
INTERFACE=interface.c interface.h
RK=readkey.c readkey.h
IPC=ipc.c ipc.h
OBJECTS=main.c $(INTERFACE) $(RK) $(IPC)
CFLAGS=-Wall -g -pedantic -ansi
LIBS=-lpthread -lpanel -lncurses
CC=gcc

all:
	$(CC) $(CFLAGS) -o $(P) $(OBJECTS) $(LIBS)

clean:
	rm -rf *.out
