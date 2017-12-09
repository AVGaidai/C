/** \file */
/*
 * Bounded knapsack problem (BKP). Dynamic programming.
 * BY GAIDAI ANATOLY
 * 2017
 */
#include <stdio.h>
#include <stdlib.h>


/**
 * \brief Bounded knapsack problem.
 *
 * \param weight is array of items weight.
 * \param value is array of items value.
 * \param N is number of items.
 * \param W is maximum weight of knapsack.
 * \param b is number of copies each items.
 *
 * \return the highest total value of a knapsack.
 */
int BKP(int *weight, int *value, int N, int W, int b)
{
   /*
    * max is array of maximum total value for any knapsack capacity (0:W)
    * used is 2D array of used items for each knapsack capacity
    */
    int i, j, k, *max, **used;

    max = (int *) calloc(W + 1, sizeof(int) * (W + 1));

    used = (int **) malloc(sizeof(int *) * (W + 1));
    for (i = 0; i <= W; ++i) {
        used[i] = (int *) calloc(N, sizeof(int) * N);
    }
    
    for (i = 1; i <= W; ++i) {
        max[i] = max[i - 1];
        for (k = 0; k < N; ++k) {
            used[i][k] = used[i - 1][k];
        }
        for (j = 0; j < N; ++j) {
            if (used[i - 1][j] < b && i - weight[j] >= 0) {
                if (value[j] + max[i - weight[j]] > max[i]) {
                    max[i] = value[j] + max[i - weight[j]];
                    for (k = 0; k < N; ++k) {
                        used[i][k] = used[i - weight[j]][k];
                    }
                    ++used[i][j];
                }
            }
        }
        printf("max[%d]=%d\n", i, max[i]);
    }


    for (i = 0; i <= W; ++i) {
        free(used[i]);
    }
    free(used);
    free(max);
    
    return max[W];
}


/**
 * \brief Main function.
 *
 * \param argv[1] is filename with items information.
 * \param argv[2] is maximum weight of knapsack.
 * \param argv[3] is number of copies each items.
 *
 * \return the integer -1 upon failure and 0 upon successful completion.
 */
int main(int argc, char *argv[])
{
    FILE *fp;
   /*
    * W is maximum weight of knapsack
    * N is number of items
    * value is array of items value
    * weight is array of items weight
    */
    int i, W, N, b, *value, *weight;
    
    if (argc < 2) {
        fprintf(stderr, "Please, input filename with "
                        "items information(weight and value)!\n");
        return -1;
    }

    if (argc < 3) {
        fprintf(stderr, "Please, input capacity of knapsack!\n");
        return -1;
    }

    if (argc < 4) {
        fprintf(stderr, "Please, input number of copies each items!\n");
        return -1;
    }

    b = atoi(argv[3]);
    W = atoi(argv[2]);
    fp = fopen(argv[1], "rb");

    fscanf(fp, "%d", &N);

    value = (int *) malloc(sizeof(int) * N);
    weight = (int *) malloc(sizeof(int) * N);
    
    for (i = 0; i < N; ++i) {
        fscanf(fp, "%d %d", &weight[i], &value[i]);
    }

    fclose(fp);
    
    printf("The highest total value of a knapsack(%d): %d\n"
           "Copies each items: %d\n", W, BKP(weight, value, N, W, b), b);
    
    free(weight);
    free(value);

    return 0;
}
    
