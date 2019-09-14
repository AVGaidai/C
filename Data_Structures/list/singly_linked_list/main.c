#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sllist.h"


int main(int argc, char *argv[])
{
    struct sllist list;
    size_t size;
    char *fname;
    
    sllist_init(&list);

    sllist_insert(&list, "file_01", 7);
    sllist_insert(&list, "file_02", 7);
    sllist_insert_back(&list, "file_03", 7);
    sllist_insert(&list, "file_04", 7);
    
    fname = sllist_eject(&list, &size);
    printf("%ld %s\n", size, fname);
    free(fname);

    sllist_insert(&list, "file_04", 7);

    fname = sllist_eject_back(&list, &size);
    printf("%ld %s\n", size, fname);
    free(fname);
    
    sllist_drop_ptr(&list);
    do {
        fname = sllist_get_curr(&list, &size);
        printf("%s\n", fname);
        free(fname);
    } while (sllist_next_node(&list) == 0);

    sllist_prev_node(&list);
    do {
        fname = sllist_eject_curr(&list, &size);
        printf("%s\n", fname);
        free(fname);
    } while (sllist_next_node(&list) == 0);
    sllist_free(&list);

    return 0;
}
