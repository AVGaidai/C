#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <string.h>


int sem_lock(int sem_id, int nsem)
{
    struct sembuf op[2];

    op[0].sem_num = nsem;
    op[0].sem_op = 0;
    op[0].sem_flg = 0;
    
    op[1].sem_num = nsem;
    op[1].sem_op = 1;
    op[1].sem_flg = 0;

    return semop(sem_id, op, 2);
}


int sem_lock_undo(int sem_id, int nsem)
{
    struct sembuf op[2];

    op[0].sem_num = nsem;
    op[0].sem_op = 0;
    op[0].sem_flg = 0;
    
    op[1].sem_num = nsem;
    op[1].sem_op = 1;
    op[1].sem_flg = SEM_UNDO;

    return semop(sem_id, op, 2);
}


int sem_unlock(int sem_id, int nsem)
{
    struct sembuf op;
    
    op.sem_num = nsem;
    op.sem_op = -1;
    op.sem_flg = 0;

    return semop(sem_id, &op, 1);
}


int sem_get_zcnt(int sem_id, int nsem)
{
    return semctl(sem_id, nsem, GETZCNT);
}

    
void ipc_initialize(int *sem_id, int *shm_id, void **shm, size_t shm_size)
{
    key_t key;
    int offset;
    
    key = ftok("./", 6);
    
    *sem_id = semget(key, 2, 0666 | IPC_CREAT | IPC_EXCL);
    if (*sem_id != -1) {
        sem_lock(*sem_id, 1);
    } else {
        *sem_id = semget(key, 2, 0666 | IPC_CREAT);
    }

    *shm_id = shmget(key, shm_size, 0666 | IPC_CREAT | IPC_EXCL);
    if (*shm_id != -1) {
        *shm = shmat(*shm_id, 0, 0);
        offset = sizeof(int);
        memcpy(*shm, &offset, sizeof(int));
    } else {
        *shm_id = shmget(key, shm_size, 0666 | IPC_CREAT);
        *shm = shmat(*shm_id, 0, 0);
    }
}


void ipc_finalize(int sem_id, int shm_id, void *shm)
{
    shmdt(shm);
    if (!semctl(sem_id, 1, GETZCNT)) {
        semctl(sem_id, 0, IPC_RMID);
        shmctl(shm_id, IPC_RMID, 0);
    }
}

