#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sllist.h"


int main(int argc, char *argv[])
{
    struct sllist list;
    FILE *fp;
    int ch, fnlen;
    size_t size;
    char *fname;
    
    sllist_init(&list);

    system("ls -a > .tmp ; cat .tmp | grep -v .tmp > .tmp1");
    system("mv .tmp1 .tmp");

    /* fp = fopen(".tmp", "rb"); */

    /* fnlen = 0; */
    /* fname = (char *) malloc(1); */
    /* while ((ch = fgetc(fp)) != EOF) { */
    /*     fname = (char *) realloc(fname, ++fnlen); */
    /*     if (ch == ' ' || ch == '\n') { */
    /*         fname[fnlen - 1] = '\0'; */
    /*         sllist_insert_back(&list, (void *) fname, fnlen); */
    /*         fnlen = 0; */
    /*         continue; */
    /*     } */
    /*     fname[fnlen - 1] = ch; */
    /* } */
    
    /* fclose(fp); */
    /* free(fname); */
    system("rm .tmp");
    
    fname = sllist_eject_back(&list, &size);
    printf("%ld %s\n", size, fname);
    free(fname);
    
    sllist_drop_ptr(&list);
    do {
        fname = sllist_get_curr(&list, &size);
        printf("%s\n", fname);
        free(fname);
    } while (sllist_next_ptr(&list) == 0);
    sllist_free(&list);

    return 0;
}
