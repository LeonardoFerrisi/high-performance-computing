#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
// to compile: mpicc -std=c99 -Wall MPI_blank_template.c -o MPI_blank
// to run (simple): mpirun ./MPI_blank

// Create Vectors

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

int main(int argc, char *argv[])
{

	int comm_sz; /* Number of processes    */
	int my_rank; /* My process rank        */

	double t1;
	double t2;

	// Don't put any MPI stuff before this line
	MPI_Init(&argc, &argv); // sets up the MPI. Always this line!

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	// printf("Comm_sz: %d\n", comm_sz);

	int SIZE;

	if ((argc < 2) || (argc > 3))
	{
		printf("usage: vectors <size> or vectors <size> <seed>\n ");
		exit(1);
	}
	else
	{
		SIZE = atoi(argv[1]); // atoi converts a string to an int
		// printf("size: %d\n\n", SIZE);
		if (argc == 3)
		{
			// printf("\nSeed is %d\n", atoi(argv[2]));
			srand(atoi(argv[2]));
		}
		else
		{
			srand(time(NULL));
		}
	}

	// Allocate space for vectors
	double *vector1 = calloc(SIZE, sizeof(double));
	double *vector2 = calloc(SIZE, sizeof(double));

	// Initial Send and Recv Blocks
	if (my_rank == 0)
	{
		// generate vectors
		vector1 = randomize_vector(vector1, SIZE);
		vector2 = randomize_vector(vector2, SIZE);

		// get my partial vector
		double partialSum = 0;

		t1 = MPI_Wtime();

		for (int i = my_rank; i < SIZE; i += comm_sz)
		{
			partialSum += (vector1[i] + vector2[i]);
			// printf("Partial Sum, i=%d: currentSum= %lf\n", i, partialSum);
		}

		if (comm_sz > 1)
		{

			for (int rank = 1; rank < comm_sz; rank++) // Send the vectors to non root nodes
			{
				// printf("Sending vector to rank: %d\n", rank);
				MPI_Send(vector1, SIZE, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD);
				MPI_Send(vector2, SIZE, MPI_DOUBLE, rank, 0, MPI_COMM_WORLD);
			}
		}

		// All nodes calculate partial sum
		double globalSum = partialSum;
		double otherPartSum;
		for (int r = 1; r < comm_sz; r++)
		{
			otherPartSum = 0;
			MPI_Recv(&otherPartSum, 1, MPI_DOUBLE, r, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			// printf("Adding partial sum from core [%d]: %lf\n", rank, otherPartSum);
			globalSum += otherPartSum;
		}
		printf("\n\n====================\nResulting Sum of Vectors: %lf\n====================", globalSum);

		// Get time for execute
		t2 = MPI_Wtime();

		double timeElapsed = t2 - t1;

		// printf("\nTime elapsed: %lf\n", timeElapsed);

		double msec = timeElapsed * 1000;

		printf("\n\nTime taken %lf seconds %lf milliseconds\n\n", msec / 1000, msec);
	}
	else // Non root nodes
	{
		MPI_Recv(vector1, SIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Recv(vector2, SIZE, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

		// printf("\n\nVECTOR 1: rank %d\n", my_rank);
		// print_vector(vector1, SIZE);
		// printf("\n");

		// printf("\n\nVECTOR 2\n");
		// print_vector(vector2, SIZE);
		// printf("\n");

		double partialSum = 0;

		// printf("\n[%d] Recieved Vector %p, %p from root node\n", my_rank, vector1, vector2);

		for (int i = my_rank; i < SIZE; i += comm_sz)
		{
			partialSum += (vector1[i] + vector2[i]);
			// printf("Partial Sum, i=%d: currentSum= %lf\n", i, partialSum);
		}

		MPI_Send(&partialSum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	// please no MPI stuff after this line
	return 0;
}