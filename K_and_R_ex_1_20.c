/** \file */
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char *input, *output, ch;
    int i = 0, step = 10, size;

    input = (char *) malloc(step * sizeof(char));
    size = step;
    printf("size: %d\n", size);
    do {
	scanf("%c", &ch);
	input[i] = ch;

	if (++i == size) {
	    input = (char *) realloc((void *) input, (size + step) * sizeof(char));
	    size += step;
	}
	printf("size: %d\n", size);
    } while (ch != '\n');
    input[i - 1] = '\0';


    printf("%s\n", input);

    free(input);
    
    return 0;
}
