#include <stdio.h>

#include "queue.h"


int main(int argc, char *argv[])
{
    int *val, i, nmemb;
    size_t size;
    struct queue queue;

    queue_init(&queue);
    
    for (i = 0; i < 10; ++i) {
        queue_push(&queue, (const void *) &i, sizeof(i));
    }

    nmemb = queue_size(&queue);
    for (i = 0; i < nmemb; ++i) {
        val = (int *) queue_pop(&queue, &size);
        printf("%d\n", *val);
    }

    printf("nmemb=%d\n", queue_size(&queue));
    
    queue_free(&queue);
    
    return 0;
}
