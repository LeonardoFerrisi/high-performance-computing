#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h> //for random seed
#include <math.h> //need to compile with -m

// being explicit here to make code more readable
#define ROOT_NODE 0

// to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
// to run (simple): mpirun ./MPI_blank

double *randomize_vector(double *vec, int size)
{
    int index;
    for (index = 0; index < size; index++)
    {
        vec[index] = rand();
    }
    return vec;
}

void print_vector(double *vec, int size)
{
    int index;
    for (index = 0; index < size; index++)
    {
        printf("%f ", vec[index]);
    }
}

double calcSumSquares(int vectorSz, double *vector, int rank, int verbose)
{
    // Calculate sum of squares
    double sumSquares = 0;
    int j;
    for (j = 0; j < vectorSz; j++)
    {
        sumSquares += vector[j] * vector[j];
    }
    if (verbose>0)
    {
        printf("\nSum of squares slice for rank: {%d}:: %lf\n", rank, sumSquares);
    }

    return sumSquares;
}

int main(int argc, char *argv[])
{

    int comm_sz; /* Number of processes    */
    int my_rank; /* My process rank        */
    int VERBOSE = 0;
    srand(time(NULL)); // should only be called once
    
    int vectorSize;

    
    double t1;
    double t2;

    if ((argc < 2) || (argc > 4))
    {
        printf("usage: vectors <size> or vectors <size> <seed> <VERBOSE>\n ");
        exit(1);
    }
    else
    {
        vectorSize = atoi(argv[1]); // atoi converts a string to an int
        if (argc == 3){srand(atoi(argv[2]));}
        if (argc == 4){VERBOSE = atoi(argv[3]);}
        else{srand(time(NULL));}  
    }


    MPI_Init(&argc, &argv); // sets up the MPI. Always this line!

    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


    int myVectorSliceSize = vectorSize / comm_sz;
    /* NOTE: Vector size must be divisible by the number of processes */
    if ((vectorSize % comm_sz) != 0)
    {
        printf("Can't do this with this number of processes\n");
    }

    /* Record the time started */
    t1 = (double)MPI_Wtime();

    double *myVector = malloc(vectorSize * sizeof(double));;
    double *myVectorSlice = malloc(myVectorSliceSize * sizeof(double));;

    /* Generate random vector in ROOT */
    if (my_rank == 0)
    {
        // myVector = 
        myVector = randomize_vector(myVector, vectorSize);
        if (VERBOSE)
        {
            printf("Full initial vector: ");
            print_vector(myVector, vectorSize);
            printf("\n\n");
        }
    }

    // PT 2: Scatter to all nodes 
    //****************************
    MPI_Scatter(myVector, myVectorSliceSize, MPI_DOUBLE, myVectorSlice, myVectorSliceSize, MPI_DOUBLE, ROOT_NODE, MPI_COMM_WORLD);

    

    // GET LOCAL SUMS and set variable for ALLSUMS
    double localSum = calcSumSquares(myVectorSliceSize, myVectorSlice, my_rank, VERBOSE);

    double *allSums = malloc(sizeof(double) * comm_sz);

    // printf("\nLocalsum for rank: {%d}:: %lf\n", my_rank, localSum);

    // GATHER ALL LOCAL SUMS INTO ALL SUMS
    MPI_Gather(&localSum, 1, MPI_DOUBLE, allSums, 1, MPI_DOUBLE, ROOT_NODE, MPI_COMM_WORLD);

    double globalMag;

    if (my_rank == 0)
    {
        double totalSum = 0;
        
        for (int i = 0; i < comm_sz; i++)
        {
            totalSum += allSums[i];
        }

        globalMag = sqrt(totalSum);
        printf("\nGlobal Mag = %lf \n", globalMag);
    }

    MPI_Scatter(myVector, myVectorSliceSize, MPI_DOUBLE, myVectorSlice, myVectorSliceSize, MPI_DOUBLE, ROOT_NODE, MPI_COMM_WORLD);
    
    MPI_Bcast(&globalMag, 1, MPI_DOUBLE, ROOT_NODE, MPI_COMM_WORLD);

    // Normalize

    for (int n = 0; n < myVectorSliceSize+1; n++)
    {   
        myVectorSlice[n] = myVectorSlice[n] / globalMag;
    }

    // ================================================
    // RE-GROUP NORMALIZED SUB VECTORS
    // ================================================
    
    MPI_Gather(myVectorSlice, myVectorSliceSize, MPI_DOUBLE, myVector, myVectorSliceSize, MPI_DOUBLE, ROOT_NODE, MPI_COMM_WORLD);

    if (my_rank == 0)
    {
        // printf("normalized vector:\n");
        // print_vector(myVector, vectorSize);
        // printf("\nVector Size: %d", vectorSize);

        printf("\nGetting resulting mag...\n");
        /* Sanity check to make sure the resulting vector is in fact, normalized */
        double finalSumSquares = calcSumSquares(vectorSize, myVector, my_rank, VERBOSE);
        double resultingMag = sqrt(finalSumSquares);
        printf("==========================\n\nResulting Magnitude: %lf\n\n==========================\n", resultingMag);

        t2 = (double)MPI_Wtime();

        printf("\n\nVector Size: {%d}, Time elapsed: {%lf}\n\n", vectorSize, t2 - t1);
    }

    MPI_Finalize();
    // please no MPI stuff after this line
    return 0;
}
