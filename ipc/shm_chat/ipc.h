#ifndef IPC_H
#define IPC_H

#include <stdio.h>


int sem_lock(int, int);
int sem_lock_undo(int, int);
int sem_unlock(int, int);
int sem_get_zcnt(int, int);
void ipc_initialize(int *, int *, void **, size_t);
void ipc_finalize(int, int, void *);

#endif
