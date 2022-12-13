/* Fire example code - step 1
 * no modifcations yet made
 */

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h> //for random seed
#include <math.h> //need to compile with -m

// being explicit here to make code more readable
#define ROOT_NODE 0

// to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
// to run (simple): mpirun ./MPI_blank

//magic of C - a function that returns a positive number of a > b, and a negative number otherwise.
//requirements of qsort are that the Compare function has to take voids are arguments
//so we cast to int inside function.
int CompareInts(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
//Use this in your MPI Sorting Code
void PrintArray(int *array, int asize)
{
    for (int i =0; i < asize; i++)
        printf(" %d ", array[i]);
    printf("\n");

}

//Use this in your MPI Sorting Code
void SortMySlice(int *slice, int slicesize)
{
    qsort(slice,slicesize,sizeof(int),CompareInts);
}

//Merges to equally sized arrays of integers
// only caring to keep the smallest items across the two arrays
// in myslice
void MergeSlicesKeepSmaller(int *myslice, int mysize, int *otherslice, int othersize)
{
   int *smallest = malloc(mysize*sizeof(int));
   int smallIndx = 0;
   int myIndex = 0;
   int otherIndex = 0;
   while (smallIndx < mysize)
   {
       int mine = myslice[myIndex];
       int others = otherslice[otherIndex];
       if (mine <= others)
       {
           smallest[smallIndx] = mine;
           myIndex++;
       }
       else
       {
           smallest[smallIndx] = others;
           otherIndex++;
       }
       smallIndx++;
   }
   memcpy(myslice, smallest, mysize*sizeof(int));
   free(smallest);
   return;
}

// Merges to equally sized arrays of integers
// only caring to keep the biggest items across the two arrays
// in myslice
void MergeSlicesKeepBigger(int *myslice, int mysize, int *otherslice, int othersize)
{
   int *biggest = malloc(mysize*sizeof(int));
   int bigIndx = mysize - 1;
   int myIndex = bigIndx;
   int otherIndex = bigIndx;
   while (bigIndx >= 0)
   {
       int mine = myslice[myIndex];
       int other = otherslice[otherIndex];
       if (mine > other)
       {
           biggest[bigIndx] = mine;
           myIndex--;
       }
       else
       {
           biggest[bigIndx] = other;
           otherIndex--;
       }
       bigIndx--;
   }
   memcpy(myslice, biggest, mysize*sizeof(int));
   free(biggest);
   return;
}

int *randomize_vector(int *vec, int size)
{
    int index;
    for (index = 0; index < size; index++)
    {
        vec[index] = rand()%101;
    }
    return vec;
}

void print_vector(int *vec, int size)
{
    int index;
    for (index = 0; index < size; index++)
    {
        printf("%d ", vec[index]);
    }
}

int main(int argc, char *argv[]) {

    int comm_sz; /* Number of processes    */
    int my_rank; /* My process rank        */

    srand(time(NULL)); // should only be called once

    int *myVector;
    int *myVectorSlice;
    int vectorSize;

    double t1;
    double t2;

    int verbose = 0;

    if ((argc < 2) || (argc > 4))
    {
        printf("usage: vectors <size> or vectors <size> <seed> <verbose>\n ");
        exit(1);
    }
    else
    {
        vectorSize = atoi(argv[1]); // atoi converts a string to an int
        // printf("size: %d\n\n", SIZE);
        if (argc == 3)
            srand(atoi(argv[2]));
        else if (argc == 4)
            verbose = atoi(argv[3]);
        else
            srand(time(NULL));
    }

    MPI_Init(&argc, &argv); // sets up the MPI. Always this line!

    /* Get the number of processes */
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    /* Get my rank among all the processes */
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // MPI_Status status;

    /* Record the time started */
    



    myVector = malloc(sizeof(int)*vectorSize);
    if (my_rank==0)
    {
        myVector = malloc(vectorSize * sizeof(int));
        myVector = randomize_vector(myVector, vectorSize);
        // print_vector(myVector, vectorSize);
    }

    int vecSliceSize = vectorSize / comm_sz;

    myVectorSlice = malloc(vecSliceSize * sizeof(int));

    if (vectorSize % comm_sz != 0)
    {
        printf("\n\nSize must by divisible by number of processes!\n\n");
        return;
    }

    t1 = MPI_Wtime();
    MPI_Scatter(myVector, vecSliceSize, MPI_INT, myVectorSlice, vecSliceSize, MPI_INT, ROOT_NODE, MPI_COMM_WORLD);
    

    //  SANITY CHECK TESTING FOR {SCATTER 1}////////////////////////////////////////
    // if (my_rank == 0)
    // {
    //     printf("\n\nThe whole vector:: {");
    //     print_vector(myVector, vectorSize);
    //     printf("}\n\n");
    // }
    // printf("\n\nNODE [%d]:: My vector: {", my_rank);
    // print_vector(myVectorSlice, vecSliceSize);
    // printf("}\n\n");

    // OK COOL COOL, SCATTERS PROPERLY
    ///////////////////////////////////////////////////

    /* Pt 2: Local Sort */
    SortMySlice(myVectorSlice, vecSliceSize);

    if (verbose){
        printf("\n\nNODE [%d]:: My vector: { ", my_rank);
        print_vector(myVectorSlice, vecSliceSize);
        printf("}\n\n");
    }
    


    // /* Pt 3A Swapping Phase */
    int *otherSlice = malloc(sizeof(int)*vecSliceSize);

    // // // Even slice?
    // int tag_send = 0;
    // int tag_recv = tag_send;
    // int sender_id = my_rank;
    // int recv_id = sender_id - 1;


    // int even_partner;
    // int odd_partnner;

    // int phase = 2;

    //EVEN PHASE

    int idx = 0;
    // printf("HELLO\n");
    while (idx < comm_sz)
    {
        if (idx % 2 == 0) // EVEN phase
        {
            if (my_rank % 2 == 0)
            {
                // even_partner = my_rank + 1;
                if (my_rank != comm_sz-1)
                {
                    if (verbose){printf("[%d] [EVEN PHASE] even: [%d]\n", my_rank, idx);}
                    MPI_Sendrecv(myVectorSlice,   vecSliceSize, MPI_INT, my_rank+1,   0, 
                            otherSlice, vecSliceSize, MPI_INT, my_rank+1,     0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MergeSlicesKeepSmaller(myVectorSlice, vecSliceSize, otherSlice, vecSliceSize);
                }
                
            }
            else // odd segment
            {
                if (verbose){printf("[%d] [EVEN PHASE] odd: [%d]\n", my_rank, idx);}
                MPI_Sendrecv(myVectorSlice,   vecSliceSize, MPI_INT, my_rank-1,   0, 
                                otherSlice, vecSliceSize, MPI_INT, my_rank-1,     0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                MergeSlicesKeepBigger(myVectorSlice, vecSliceSize, otherSlice, vecSliceSize);
            }

        } 

        else
        {
            // even_partner = my_rank + 1;
            if (my_rank % 2 == 0)
            {
                if (my_rank != 0)
                {
                    if (verbose){printf("[%d] [ODD PHASE] even: [%d]\n", my_rank, idx);}
                    MPI_Sendrecv(myVectorSlice,   vecSliceSize, MPI_INT, my_rank-1,   0, 
                            otherSlice, vecSliceSize, MPI_INT, my_rank-1,     0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MergeSlicesKeepBigger(myVectorSlice, vecSliceSize, otherSlice, vecSliceSize);
                }
            }
                
            else // odd segment
            {
                if (my_rank != comm_sz - 1)
                {
                    if (verbose) {printf("[%d] [ODD PHASE] odd [%d]\n",my_rank, idx);}
                    MPI_Sendrecv(myVectorSlice,   vecSliceSize, MPI_INT, my_rank+1,   0, 
                                    otherSlice, vecSliceSize, MPI_INT, my_rank+1,     0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    MergeSlicesKeepSmaller(myVectorSlice, vecSliceSize, otherSlice, vecSliceSize);
                }
            }
            
        }
        idx+=1;
    }

    MPI_Gather(myVectorSlice, vecSliceSize, MPI_INT, myVector, vecSliceSize, MPI_INT, ROOT_NODE, MPI_COMM_WORLD);

    if (my_rank == ROOT_NODE)
    {
        // printf("\n==================\n");
        
        for (int i = 1; i < vectorSize; i++)
        {
            int prev = myVector[i-1];
            int current = myVector[i];
            if (prev > current)
            {
                printf("SORT DID NOT COMPLETE CORRECTLY\n");
                return;
            }
        }
        if (verbose)
        {
            print_vector(myVector, vectorSize);
        }


        t2 = (double)MPI_Wtime();
        printf("\n\nVector Size: {%d}, Time elapsed: {%lf}\n\n", vectorSize, t2 - t1);


    }


    MPI_Finalize();
    // please no MPI stuff after this line
    return 0;
}
