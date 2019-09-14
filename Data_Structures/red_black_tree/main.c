#include <stdio.h>
#include <unistd.h>

#include "inc/RBT.h"

int main()
{
    RB_Tree T;
    
    RBT_Init(&T);

    int value = 2;
    int status = 0;
    size_t size;
    int *v;

    RBT_Print(&T);
    
    RBT_Insert(&T, 11, &value, sizeof(value));
    RBT_Insert(&T, 22, &value, sizeof(value));
    RBT_Insert(&T, 7, &value, sizeof(value));
    RBT_Insert(&T, 13, &value, sizeof(value));
    RBT_Insert(&T, 1, &value, sizeof(value));
    RBT_Insert(&T, 0, &value, sizeof(value));
    value = 111;
    RBT_Insert(&T, 111, &value, sizeof(value));
    RBT_Print(&T);

    status = RBT_Find(&T, 111, (void **) &v, &size);
    if (!status)
	printf("size: %ld; value: %d\n", size, *v);
    else
	printf("element not found!\n");


    //    sleep(3);
    RBT_Insert(&T, -1, &value, sizeof(value));
    RBT_Print(&T);

    //sleep(3);
    RBT_Insert(&T, 21, &value, sizeof(value));
    RBT_Print(&T);

    //sleep(3);
    RBT_Insert(&T, -4, &value, sizeof(value));
    RBT_Print(&T);

    //sleep(3);
    RBT_Insert(&T, 25, &value, sizeof(value));
    RBT_Print(&T);

    //sleep(3);
    RBT_Insert(&T, 33, &value, sizeof(value));
    RBT_Print(&T);

    

    
    RBT_Delete(&T, 11);
    //sleep(3);

    RBT_Print(&T);

    RBT_Delete(&T, 111);
    //sleep(3);

    RBT_Print(&T);
    RBT_Delete(&T, 0);
    //sleep(3);

    RBT_Print(&T);
    RBT_Delete(&T, 7);
    //sleep(3);

    RBT_Print(&T);
    RBT_Delete(&T, 13);
    //sleep(3);

    RBT_Print(&T);
    RBT_Delete(&T, 1);
    //sleep(3);

    RBT_Print(&T);


    status = RBT_Find(&T, 22, (void **) &v, &size);
    if (!status)
	printf("size: %ld; value: %d\n", size, *v);
    else
	printf("element not found!\n");

    RBT_Free(&T);
}

	
