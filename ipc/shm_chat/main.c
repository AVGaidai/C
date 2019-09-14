#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include "ipc.h"
#include "interface.h"


#define SHM_SIZE 1024


void *shm;
int shm_id, sem_id;
int stop_chat;

void *scan_func(void *arg)
{
    char buf[SHM_SIZE - sizeof(int)];
    int offset;
    size_t lbuf;
    
    while (1) {
        
        lbuf = msg_scan(buf, SHM_SIZE - (sizeof(int)));

        if (lbuf == -1) {
            stop_chat = 1;
            pthread_exit(NULL);
        }
        
        if (sem_lock(sem_id, 0)) {
            pthread_exit(NULL);
        }
        
        memcpy(&offset, shm, sizeof(int));
        if (SHM_SIZE - offset < lbuf) {
            offset = sizeof(int);
        }
      
        memcpy(shm + offset, buf, lbuf);
        offset += lbuf;
        memcpy(shm, &offset, sizeof(int));
        if (sem_unlock(sem_id, 1)) {
            pthread_exit(NULL);
        }
        if (sem_lock(sem_id, 1)) {
            pthread_exit(NULL);
        }
        if (sem_unlock(sem_id, 0)) {
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}


void *print_func(void *arg)
{
    char buf[SHM_SIZE - sizeof(int)];
    size_t lbuf;
    
    stop_chat = 0;
    while (!stop_chat) {
        if (sem_lock(sem_id, 1)) {
            pthread_exit(NULL);
        }
        memcpy(&lbuf, shm, sizeof(int));
        lbuf -= sizeof(int);
        memcpy(buf, shm + sizeof(int), lbuf);
        msg_print(buf, lbuf);
        if (sem_unlock(sem_id, 1)) {
            pthread_exit(NULL);
        }
    }

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    pthread_t print_thr, scan_thr;

    ipc_initialize(&sem_id, &shm_id, &shm, SHM_SIZE);
    initialize();
    
    if (pthread_create(&print_thr, NULL, print_func, NULL)) {
        ipc_finalize(sem_id, shm_id, shm);
        exit(1);
    }

    if (pthread_create(&scan_thr, NULL, scan_func, NULL)) {
        ipc_finalize(sem_id, shm_id, shm);
        exit(1);
    }

    pthread_join(scan_thr, NULL);

    sem_unlock(sem_id, 1);
    sem_lock(sem_id, 1);
    pthread_join(print_thr, NULL);
    
    ipc_finalize(sem_id, shm_id, shm);
    finalize();
    
    return 0;
}
