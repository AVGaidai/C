#define _ISOC99_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <time.h>

#include <math.h>


#include "../queue/queue.h"


struct task {

    int id;
    int time;
    int step;
    
};



int task_add(struct task *task, struct queue *queue)
{
    return queue_push(queue, task, sizeof(struct task));
}


void modeling(struct queue *queue, int *t, int k, int T)
{
    int i, j;
    int *status;
    size_t size;
    struct task **task;

    task = (struct task **) malloc(k * sizeof(struct task *));
    for (i = 0; i < k; ++i) {
        task[i] = (struct task *) malloc(sizeof(struct task));
    }
    
    status = (int *) calloc(k, k * sizeof(int));
    for (i = 0; i < T; ++i) {
        for (j = 0; j < k; ++j) {
            if (status[j] == 1) {
                if (--(task[j]->time) == 0) {
                    status[j] = 2;
                } 
            } else if (status[j] == 0) {
                task[j] = (struct task *) queue_pop(&queue[j], &size);
                if (task[j] == NULL) continue;
                status[j] = 1;
                if (--(task[j]->time) == 0) {
                    status[j] = 2;
                }
            }
        }
        for (j = 0; j < k; ++j) {
            if (status[j] == 2) {
                task[j]->time = t[(j + 1) % k];
                ++(task[j]->step);
                task_add(task[j], &queue[(j + 1) % k]);
                status[j] = 0;
            }
        }
    }
    
    for (i = 0; i < k; ++i) {
        if (status[i] == 1) {
            task_add(task[i], &queue[i]);
        }
        free(task[i]);
    }
    free(task);
    free(status);
}


int main(int argc, char *argv[])
{
    int k = 5, N = 10, T = 1000;
    int i, opt, r;
    int *t;
    size_t size;
    double *sigma, x;
    struct queue *queue;
    struct task task, *t1;
    
    while ((opt = getopt(argc, argv, "k:N:T:")) != -1) {
        switch (opt) {
        case 'k':
            k = atoi(optarg);
            break;
        case 'N':
            N = atoi(optarg);
            break;
        case 'T':
            T = atoi(optarg);
            break;
        default:
            ;
        }
    }
    printf("k=%d\nN=%d\nT=%d\n", k, N, T);

    sigma = (double *) malloc(k * sizeof(double));
    t = (int *) malloc(k * sizeof(int));
    queue = (struct queue *) malloc(k * sizeof(struct queue));
    
    srand(time(NULL));
    for (i = 0; i < k; ++i) {
        x = (double) rand() / (double) RAND_MAX;
        sigma[i] = 1 - exp((i + 1) * x * -1.00);
        t[i] = (int) round(sigma[i] * 10);
        printf("sigma%d: %f (%d)\n", i + 1, sigma[i], t[i]);
        queue_init(&queue[i]);
    }


    for (i = 0; i < N; ++i) {
        r = rand() % k;
        task.id = i;
        task.time = t[r];
        task.step = 0;
        task_add(&task, &queue[r]);
    }


    modeling(queue, t, k, T);

    
    for (i = 0; i < k; ++i) {
        printf("\nDevice %d: \n{\n", i);
        while ((t1 = (struct task *) queue_pop(&queue[i], &size)) != NULL) {
            printf("t%d(time: %d, cycle: %d)\n",
                   t1->id, t1->time, t1->step / k);
        }
        printf("}\n");
        queue_free(&queue[i]);
    }
    
    free(queue);
    free(t);
    free(sigma); 
    
    return 0;
}
