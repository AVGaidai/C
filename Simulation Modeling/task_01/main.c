#define _ISOC99_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>

#include <time.h>

#include <math.h>


#include "../queue/queue.h"

struct task {

    double arrival_time;
    int id;

};


struct event {

    double time;
    int device_num;
    int task_num;

};


struct device {

    double time;
    int id;
    int completed_tasks;

    struct task *task;
    struct queue queue;
    
};


int compare(const void *a, const void *b)
{
    double t1, t2;
    
    struct device d1, d2;

    d1 = *((struct device *) a);
    d2 = *((struct device *) b);

    t1 = d1.completed_tasks * d1.time + d1.time;
    if (d1.task != NULL) {
        t1 += d1.task->arrival_time;
    }

    t2 = d2.completed_tasks * d2.time + d2.time;
    if (d2.task != NULL) {
        t2 += d2.task->arrival_time;
    }

    return (t1 > t2) ? 1 : 0;
}


void schedule_create(struct queue *schedule,
                     struct device *device, int k, int T)
{
    int i, j;
    size_t size;

    struct event event;
        
    for (i = 0; i < k; ++i) {
        if (device[i].task != NULL) {
            
            device[i].task->arrival_time +=
                device[i].time * (device[i].completed_tasks++) + device[i].time;

            for (j = 0; device[j].id != (device[i].id + 1) % k; ++j);
            queue_push(&(device[j].queue), device[i].task, sizeof(struct task));

            if (device[j].task == NULL) {
                device[j].task = (struct task *)
                    queue_pop(&(device[j].queue), &size);
            }
            
            event.time = device[i].task->arrival_time;
            if (event.time > T) {
                queue_free(&(device[i].queue));
                free(device[i].task);
                continue;
            }
            event.device_num = device[i].id;
            event.task_num = device[i].task->id;
            queue_push(schedule, &event, sizeof(struct event));

            free(device[i].task);
            device[i].task = (struct task *)
                queue_pop(&(device[i].queue), &size);

            qsort(device, k, sizeof(struct device), compare);
            i = -1;
        }
    }
}


int main(int argc, char *argv[])
{
    int k = 5, N = 10, T = 1000;
    int i, opt;
    size_t size;
    double x;
    
    struct event *event;
    struct queue schedule;
    struct device *device;
    struct task *task;
    
        
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

    device = (struct device *) malloc(k * sizeof(struct device));
    
    srand(time(NULL));
    
    for (i = 0; i < k; ++i) {
        x = rand() / (double) RAND_MAX;
        device[i].time = -1.00 * log(1.00 - x) / (i + 1);
        device[i].id = i;
        queue_init(&(device[i].queue));
    }
    device[0].time = 1.98;
    device[1].time = 0.66;
    device[2].time = 0.13;
    device[3].time = 0.11;
    device[4].time = 0.08;
    
    qsort(device, k, sizeof(struct device), compare);

    task = (struct task *) malloc(N * sizeof(struct task));
    
    for (i = 0; i < N; ++i) {
        task[i].arrival_time = 0.00;
        task[i].id = i;
        printf("%d\n", i % k);
        queue_push(&(device[i % k].queue), &task[i], sizeof(struct task));
    }

    for (i = 0; i < k; ++i) {
        printf("device #%d time: %f\n", device[i].id, device[i].time);
        device[i].task = (struct task *) queue_pop(&(device[i].queue), &size);
    }

    queue_init(&schedule);
    schedule_create(&schedule, device, k, T);

    while ((event = (struct event *) queue_pop(&schedule, &size)) != NULL) {
        printf("Event (time=%f): task %d from device #%d to device #%d\n",
               event->time, event->task_num,
               event->device_num, (event->device_num + 1) % k);
    }
    queue_free(&schedule);
    free(task);
    
    for (i = 0; i < k; ++i) {
        queue_free(&(device[i].queue));
    }
    
    free(device);
    
    return 0;
}
