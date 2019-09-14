/** \file */
/*
 * Unbounded knapsack problem (UKP). Dynamic programming.
 * BY GAIDAI ANATOLY
 * 2017
 */
#include <stdio.h>
#include <stdlib.h>


/**
 * \brief Unbounded knapsack problem.
 *
 * \param weight is array of items weight.
 * \param value is array of items value.
 * \param N is number of items.
 * \param W is maximum weight of knapsack.
 *
 * \return the highest total value of a knapsack.
 */
int UKP(int *weight, int *value, int N, int W)
{
    int i, j, *max;

    max = (int *) calloc(W + 1, sizeof(int) * (W + 1));
    
    for (i = 1; i <= W; ++i) {
        for (j = 0; j < N; ++j) {
            if (i - weight[j] >= 0) {
                max[i] = (value[j] + max[i - weight[j]] > max[i])
                    ? value[j] + max[i - weight[j]]
                    : max[i];
            }
        }
    }

    free(max);

    return max[W];
}


/**
 * \brief Main function.
 *
 * \param argv[1] is filename with items information.
 * \param argv[2] is maximum weight of knapsack.
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
    int i, W, N, *value, *weight;
    
    if (argc < 2) {
        fprintf(stderr, "Please, input filename with "
                        "items information(weight and value)!\n");
        return -1;
    }

    if (argc < 3) {
        fprintf(stderr, "Please, input capacity of knapsack!\n");
        return -1;
    }

    W = atoi(argv[2]);
    fp = fopen(argv[1], "rb");

    fscanf(fp, "%d", &N);

    value = (int *) malloc(sizeof(int) * N);
    weight = (int *) malloc(sizeof(int) * N);
    
    for (i = 0; i < N; ++i) {
        fscanf(fp, "%d %d", &weight[i], &value[i]);
    }

    fclose(fp);
    
    printf("The highest total value of a knapsack(%d): %d\n",
           W, UKP(weight, value, N, W));
    
    free(weight);
    free(value);

    return 0;
}
    
