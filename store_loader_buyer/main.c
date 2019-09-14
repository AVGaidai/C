/** \file */
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


#define FREE 0
#define BUSY 1


#define NSTORES             5
#define NBUYERS             3
#define LB_STORE_START_VAL  1000
#define RB_STORE_START_VAL  1200
#define LB_LOADER_CAPACITY  300
#define RB_LOADER_CAPACITY  500
#define LB_NEEDS_BUYER      3000
#define RB_NEEDS_BUYER      3500


/**
 * \brief Data structure for describe store
 *
 * The "status" field displays the status of the store;
 * the "val" field displays the quantity of goods in the store.
 */
struct store {
    
    int status;
    int val;    

};


pthread_cond_t cv;
pthread_mutex_t cm;

bool stop, cond;


struct store stores[NSTORES];


/**
 * \brief This function sets initial values for stores
 *
 * \param "stores" is pointer to stores array
 */
void init_stores(struct store *stores)
{
    int i;
    
    for (i = 0; i < NSTORES; ++i) {
        stores[i].val = rand() % (RB_STORE_START_VAL - LB_STORE_START_VAL + 1)
                        + LB_STORE_START_VAL;
        stores[i].status = FREE;
    }
}

/**
 * \brief This thread function for loader
 *
 * \param "arg" is thread info (empty)
 */ 
void *loader(void *arg)
{
   /*
    * ncs -- number of current store
    */
    int ncs;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);

    pthread_mutex_lock(&cm);
    while (!cond) {
        pthread_cond_wait(&cv, &cm);
    }
    pthread_mutex_unlock(&cm);
    
    while (!stop) {
        do {
            ncs = rand() % NSTORES;
        } while (stores[ncs].status == BUSY);
        pthread_mutex_lock(&mutex);
        stores[ncs].status = BUSY;
        pthread_mutex_unlock(&mutex);
        stores[ncs].val += rand() % (RB_LOADER_CAPACITY - LB_LOADER_CAPACITY)
                           + LB_LOADER_CAPACITY;
        sleep(1);
        pthread_mutex_lock(&mutex);
        stores[ncs].status = FREE;
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_destroy(&mutex);
    
    pthread_exit(NULL);
}



/**
 * \brief This thread function for buyer
 *
 * \param "arg" is thread info (empty)
 */
void *buyer(void *arg)
{
   /*
    * ncs -- number of current store
    */
    int ncs, needs;
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, NULL);
    
    needs = rand() % (RB_NEEDS_BUYER - LB_NEEDS_BUYER + 1) + LB_NEEDS_BUYER;

    pthread_mutex_lock(&cm);
    while (!cond) {
        pthread_cond_wait(&cv, &cm);
    }
    pthread_mutex_unlock(&cm);
    
    while (needs != 0) {
        do {
            ncs = rand() % NSTORES;
        } while (stores[ncs].status == BUSY);
        pthread_mutex_lock(&mutex);
        stores[ncs].status = BUSY;
        pthread_mutex_unlock(&mutex);
        if (stores[ncs].val == 0) {
            pthread_mutex_lock(&mutex);
            stores[ncs].status = FREE;
            pthread_mutex_unlock(&mutex);
            sleep(3);
            continue;
        } else if (needs >= stores[ncs].val) {
            needs -= stores[ncs].val;
            stores[ncs].val = 0;
        } else {
            stores[ncs].val -= needs;
            needs = 0;
        }
        pthread_mutex_lock(&mutex);
        stores[ncs].status = FREE;
        pthread_mutex_unlock(&mutex);
    }

    pthread_mutex_destroy(&mutex);
    
    pthread_exit(NULL);    
}



/**
 * \brief This main task function
 */
int main(int argc, char *argv[])
{
    pthread_t thr_loader, thr_buyers[NBUYERS];
    int i;

    srand(time(NULL));
    
    stop = 0;
    cond = 0;
    
    pthread_cond_init(&cv, NULL);
    pthread_mutex_init(&cm, NULL);
    
    init_stores(stores);

    pthread_create(&thr_loader, NULL, &loader, NULL);

    for (i = 0; i < NBUYERS; ++i) {
        pthread_create(&thr_buyers[i], NULL, &buyer, NULL);
    }

    cond = 1;
    pthread_cond_broadcast(&cv);
    
    for (i = 0; i < NBUYERS; ++i) {
        pthread_join(thr_buyers[i], NULL);
    }

    stop = 1;

    pthread_join(thr_loader, NULL);

    pthread_mutex_destroy(&cm);
    pthread_cond_destroy(&cv);
    
    return 0;
}
