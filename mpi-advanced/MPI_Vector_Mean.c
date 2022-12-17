#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> //for random seed
#include <math.h> //need to compile with -m
// to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
// to run (simple): mpirun ./MPI_blank

int *randomize_vector(int *vec, int size, int seed, int my_rank)
{
    srand(seed*my_rank);
    for (int index = 0; index < size; index++)
    {
        vec[index] = rand() % 101;
    }
    return vec;
}

int calcSum(int *array, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += abs(array[i]);
    }
    return abs(sum);
}

int main(int argc, char *argv[])
{

    int comm_sz; /* Number of processes    */
    int my_rank; /* My process rank        */
    // Don't put any MPI stuff before this line
    MPI_Init(&argc, &argv); // sets up the MPI. Always this line!

    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int SIZE;

    int VERBOSE = 0;

    double t1;
    double t2;

    int SEED;

    if ((argc < 2) || (argc > 4))
    {
        printf("usage: vectors <size> or vectors <size> <seed> <VERBOSE>\n ");
        exit(1);
    }
    else
    {
        SIZE = atoi(argv[1]); // atoi converts a string to an int
        if (argc == 3)
        {   
            SEED = atoi(argv[2]);
            srand(SEED);
        }
        if (argc == 4)
        {
            VERBOSE = atoi(argv[3]);
        }
        else
        {
            srand(time(NULL));
        }
    }

    if (SIZE % comm_sz != 0)
    {
        printf("\n\nSize must by divisible by number of processes!\n\n");
        exit(1);
    }

    int localSize = SIZE / comm_sz;


    // int *masterArray = malloc(sizeof(int)*SIZE);

    int *localArray = malloc(sizeof(int)*localSize);

    int localSum;
    int globalSum = 0;

    t1 = MPI_Wtime();

    // make local array
    localArray = randomize_vector(localArray, localSize, SEED, my_rank);

    // calc local sum
    localSum = calcSum(localArray, localSize);
    
    // globalSum = 0;

    printf("\n[%d] localSum: %d\n", my_rank, localSum);

    MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        printf("\n[%d] globalSum: %d\n", my_rank, abs(globalSum));
        double arrayMean = (double) abs(globalSum / comm_sz);

        printf("\nArray Mean: %lf\n", arrayMean);

        t2 = MPI_Wtime();
        printf("\n\nVector Size: {%d}, Time elapsed: {%lf}\n\n", SIZE, t2 - t1);
    }

    MPI_Finalize();
    // please no MPI stuff after this line
    return 0;
}