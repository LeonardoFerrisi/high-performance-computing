#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> //for random seed
#include <math.h> //need to compile with -m
//to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
//to run (simple): mpirun ./MPI_blank


void print_vector(int *vec, int size, int rank)
{
    printf("\n[%d] ", rank);
    int index;
    for (index = 0; index < size; index++)
    {
        printf("%d ", vec[index]);
    }
}

int *randomize_vector(int *vec, int size, int rank, int seed)
{
    srand((rank+1)*seed);
    int index;
    for (index = 0; index < size; index++)
    {
        vec[index] = rand()%101;
    }
    return vec;
}

int calcSum(int *array, int size)
{
    int sum = 0;
    for (int i=0; i < size; i++)
    {
        sum+=array[i];
    }
    return sum;
}

double calcSumSquaredDiffs(int *array, int size, double mean)
{
    double sum=0;
    for (int i = 0; i < size; i++)
    {   
        double localSquaredDiff = ((mean - array[i]) * (mean - array[i]));
        sum+=localSquaredDiff;
    }
    return sum;
}


int main(int argc, char *argv[]){
	int        comm_sz;               /* Number of processes    */
	int        my_rank;               /* My process rank        */
	//Don't put any MPI stuff before this line
	MPI_Init(&argc, &argv);  //sets up the MPI. Always this line!


	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    

    int SIZE;

    int VERBOSE = 0;

    int SEED;

    double t1;
    double t2;

    if ((argc < 2) || (argc > 4))
    {
        printf("usage: vectors <size> or vectors <size> <seed> <VERBOSE>\n ");
        exit(1);
    }
    else
    {
        SIZE = atoi(argv[1]); // atoi converts a string to an int
        if (argc == 3){SEED = atoi(argv[2]);}
        if (argc == 4){VERBOSE = atoi(argv[3]);}
        else{SEED = time(NULL);}  
    }

    if (SIZE % comm_sz != 0)
    {
        printf("\n\nSize must by divisible by number of processes!\n\n");
        exit(0);
    }

    int localSize = SIZE/comm_sz;
    // int * masterArray = malloc(sizeof(int));
    int * localArray = malloc(sizeof(int)*localSize);

    int localSum;
    int globalSum = 0;
    

    // make local array
    localArray = randomize_vector(localArray, localSize, my_rank, SEED);

    if (VERBOSE)
    {
        // print_vector(localArray, localSize, my_rank);
    }
    

    // calc local sum
    
    localSum = calcSum(localArray, localSize);
    
    t1 = MPI_Wtime();

    if (VERBOSE)
    {
        printf("\n[%d] localSum: %d\n", my_rank, localSum);
    }

    MPI_Allreduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    double globalMean = globalSum / SIZE;

    double localSumSquaredDiffs = calcSumSquaredDiffs(localArray, localSize, globalMean);

    double globalSumSquaredDiffs;

    MPI_Reduce(&localSumSquaredDiffs, &globalSumSquaredDiffs, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


    if (my_rank == 0)
    {
        double sigma = sqrt(globalSumSquaredDiffs / SIZE);
        printf("\nStandard Deviation: %lf\n", sigma);


        t2 = MPI_Wtime();
        printf("\n\nVector Size: {%d}, Time elapsed: {%lf}\n\n", SIZE, (t2 - t1)*1000);

    }
    

	MPI_Finalize();
	//please no MPI stuff after this line
	return 0;
}