#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <dlfcn.h>

#include "include/complex_num.h"

	
/**
 * Executing "ls -1 'path'" and save result to list.
 * \param *path -- path to directory;
 * \param ***list -- pointer to storage container list.
 */ 
int list_dir(const char *path, char ***list)
{
    char *command;

   /* 
    * Creating command "ls -1 'path' >> .list_dir"
    * .list_dir -- temporary files
    */
    command = (char *) malloc(strlen("ls -1 ") +
			      strlen(path) +
			      strlen(" > .list_dir"));
    memcpy(command, "ls -1 ", strlen("ls -1 "));
    memcpy(command + strlen("ls -1 "), path, strlen(path));
    memcpy(command + strlen("ls -1 ") + strlen(path),
	   " > .list_dir", strlen(" > .list_dir"));

    system(command);   // Execution command "ls -1 'path' >> .list_dir" 
    free(command);

    FILE *fp = fopen(".list_dir", "rb");

    char *fname;
    int len = 0, size = 0, c;

   /*
    * Forming storage container list
    */
    c = fgetc(fp);
    while (c != EOF) {
	fname = (char *) realloc(fname, ++len);
	fname[len - 1] = c;
	if (c == '\n') {
	    fname[len - 1] = '\0';
	    *list = (char **) realloc(*list, sizeof(char *) * (++size));
	    (*list)[size - 1] = (char *) malloc(len);
	    memcpy((*list)[size - 1], fname, len);
	    len = 0;
	}
	c = fgetc(fp);
    }

    fclose(fp);
    system("rm -rf ./.list_dir");
    free(fname);
    return size;
}

   
int main(void)
{
    char **list = NULL;
    int size;

    size = list_dir("./plugins/*.so", &list);

    int ADDF, SUBF, MULF, DIVF;

    ADDF = SUBF = MULF = DIVF = 1;
    for (int i = 0; i < size; ++i) {
	ADDF *= strcmp("./plugins/libcomplex_add.so", (const char *) list[i]);
	SUBF *= strcmp("./plugins/libcomplex_sub.so", (const char *) list[i]);
	MULF *= strcmp("./plugins/libcomplex_mul.so", (const char *) list[i]);
	DIVF *= strcmp("./plugins/libcomplex_div.so", (const char *) list[i]);
    }
    
    Complex_Num A, B, C;

    printf("\E[H\E[2J");
    printf( "Enter the first complex number "
            "as a pair of numbers with a space:\n> " );
    scanf("%lf %lf", &A.Re, &A.Im);

    printf( "Enter the second complex number "
            "as a pair of numbers with a space:\n> " );
    scanf("%lf %lf", &B.Re, &B.Im);

    int act = 0;

    void *handle;
    Complex_Num (*action)(Complex_Num, Complex_Num);

    int cnt = 1;
    
    printf("Select action:\n");
    if (!ADDF) printf("%d) Addition\n", ADDF = cnt++);
    else ADDF = -1;
    if (!SUBF) printf("%d) Subtraction\n", SUBF = cnt++);
    else SUBF = -2;
    if (!MULF) printf("%d) Multiplication\n", MULF = cnt++);
    else MULF = -3;
    if (!DIVF) printf("%d) Devision\n", DIVF = cnt++);
    else DIVF = -4;
    printf("0) Nothing\n\n");
    do {
        printf("> ");
        scanf("%d", &act);
	if (act > 0 && act == ADDF) {
	    printf("A + B = C\n");
	    handle = dlopen("./plugins/libcomplex_add.so", RTLD_LAZY);
	    action = (Complex_Num (*)(Complex_Num, Complex_Num)) 
		      dlsym(handle, "cn_add");
	    C = action(A, B);
	    dlclose(handle);
	} else if (act > 0 && act == SUBF) {
	    printf("A - B = C\n");
	    handle = dlopen("./plugins/libcomplex_sub.so", RTLD_LAZY);
	    action = (Complex_Num (*)(Complex_Num, Complex_Num)) 
                      dlsym(handle, "cn_sub");
	    C = action(A, B);
	    dlclose(handle);
	} else if (act > 0 && act == MULF) {
	    printf("A * B = C\n");
	    handle = dlopen("./plugins/libcomplex_mul.so", RTLD_LAZY);
	    action = (Complex_Num (*)(Complex_Num, Complex_Num)) 
                      dlsym(handle, "cn_mul");
	    C = action(A, B);
	    dlclose(handle);
	} else if (act > 0 && act == DIVF) {
	    printf("A / B = C\n");
	    handle = dlopen("./plugins/libcomplex_div.so", RTLD_LAZY);
	    action = (Complex_Num (*)(Complex_Num, Complex_Num)) 
                      dlsym(handle, "cn_div");
	    C = action(A, B);
	    dlclose(handle);
	}
    } while (act < 0 || act > cnt - 1);
    
    if (act) {
        printf("A = (%.2lf) + i*(%.2lf)\n", A.Re, A.Im);
        printf("B = (%.2lf) + i*(%.2lf)\n", B.Re, B.Im);
        printf("C = (%.2lf) + i*(%.2lf)\n", C.Re, C.Im);
    }
    for (int i = 0; i < size; ++i)
	free(list[i]);
    free(list);
}

