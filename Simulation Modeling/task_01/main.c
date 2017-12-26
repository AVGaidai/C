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
    int transition;
    
};


struct event {

    double time;
    int device_id;
    int task_id;
    
};


struct device {

    double time;
    double last_time;
    int id;

    struct task *task;
    struct queue queue;
    
};


int compare(const void *a, const void *b)
{
    double t1, t2;
    
    struct device d1, d2;

    d1 = *((struct device *) a);
    d2 = *((struct device *) b);

    t1 = d1.last_time;
    if (d1.task != NULL) {
        t1 = (d1.task->arrival_time > t1) ? d1.task->arrival_time : t1;
    }
    t1 += d1.time;
    

    t2 = d2.last_time;
    if (d2.task != NULL) {
        t2 = (d2.task->arrival_time > t2) ? d2.task->arrival_time : t2;
    }
    t2 += d2.time;
    
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

            if (device[i].last_time < device[i].task->arrival_time) {
                device[i].last_time = device[i].task->arrival_time;
            }
            device[i].task->arrival_time = device[i].last_time + device[i].time;
            device[i].last_time = device[i].task->arrival_time;
            
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
            event.device_id = device[i].id;
            event.task_id = device[i].task->id;
            queue_push(schedule, &event, sizeof(struct event));

            free(device[i].task);
            device[i].task = (struct task *)
                queue_pop(&(device[i].queue), &size);

            qsort(device, k, sizeof(struct device), compare);
            i = -1;
        }
    }
}



struct event *get_event(struct queue *schedule)
{
    size_t size;
    
    return (struct event *) queue_pop(schedule, &size);
}


void execute_event(struct event *event, struct task *task)
{
    ++task[event->task_id].transition;
}


void remove_event(struct event *event)
{
    free(event);
}


int main(int argc, char *argv[])
{
    int k = 5, N = 10;
    int i, j, r, opt, events_num;
    int *distr, *state;
    size_t size;
    double x, T = 1000.00;
        
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
            T = atof(optarg);
            break;
        default:
            ;
        }
    }

    if (T <= 0.0 || N <= 0 || k <= 0) {
        return 1;
    }
    
    printf("k=%d\nN=%d\nT=%.2f\n", k, N, T);

    device = (struct device *) malloc(k * sizeof(struct device));
    
    srand(time(NULL));
    
    for (i = 0; i < k; ++i) {
        x = rand() / (double) RAND_MAX;
        device[i].time = -1.00 * log(1.00 - x) / (i + 1);
        device[i].last_time = 0.00;
        device[i].id = i;
        queue_init(&(device[i].queue));
    }
    
    qsort(device, k, sizeof(struct device), compare);

    task = (struct task *) malloc(N * sizeof(struct task));
    state = (int *) calloc(k, k * sizeof(int));
    for (i = 0; i < N; ++i) {
        task[i].arrival_time = 0.00;
        task[i].id = i;
        task[i].transition = 0;
        r = rand() % k;
        for (j = 0; device[j].id != r; ++j);            
        queue_push(&(device[j].queue), &task[i], sizeof(struct task));
        ++state[device[j].id];
    }

    for (i = 0; i < k; ++i) {
        printf("device #%d time: %f | start task number %d\n",
               device[i].id, device[i].time, state[device[i].id]);
        device[i].task = (struct task *) queue_pop(&(device[i].queue), &size);
    }

    queue_init(&schedule);
    schedule_create(&schedule, device, k, T);

    distr = (int *) calloc(k, k * sizeof(int));
    events_num = 0;
    while ((event = get_event(&schedule)) != NULL) {
        ++events_num;
        --state[event->device_id];
        ++state[(event->device_id + 1) % k];
        for (i = 0; i < k; ++i) {
            distr[i] += state[i];
        }
        printf("Event (time=%f): task %d from device #%d to device #%d"
               " | %d tasks on device %d\n",
               event->time, event->task_id,
               event->device_id, (event->device_id + 1) % k,
               state[event->device_id], event->device_id);
        execute_event(event, task);
        remove_event(event);
    }
    queue_free(&schedule);
    free(state);

    printf("distr: ");
    for (i = 0; i < k; ++i) {
        printf("%f ", ((distr[i] / (double) events_num) * 100.0) / (double) N);
    }

    free(distr);
    printf("\n\n=====================\n");
    for (i = 0; i < N; ++i) {
        printf("task #%d\n"
               "_____________________________\n"
               "\tcycle number: %d\n"
               "\tavg cycle time: %f\n\n",
               i, task[i].transition / k, T / (task[i].transition / k));
    }
    printf("=====================\n");    
    
    free(task);
    
    for (i = 0; i < k; ++i) {
        queue_free(&(device[i].queue));
    }
    
    free(device);
    
    return 0;
}
