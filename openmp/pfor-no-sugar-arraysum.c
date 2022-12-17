#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  int PiVals[10] = {3,1,4,1,5,9,2,6,5,4};

  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);
	int globalsum = 0;

double t1 = omp_get_wtime();
  #pragma omp parallel num_threads(nthreads)
{
	int myid = omp_get_thread_num();
	int threadcount = omp_get_num_threads(); //like, super-high threadcount sheets?
	int localsum = 0;
	for (int i = myid ; i < 10; i+=threadcount)
	{
		localsum+=PiVals[i]; // We wanna add all the elements of pi
	}
	#pragma omp critical 
	globalsum+=localsum;
	
	//do something here to (atomically) aggregate local sums into a global sum
} //end of pfor pragma
double t2 = omp_get_wtime();
printf("global sum is %d, time elapsed: {%f}\n",globalsum, (t2-t1)*1000);
}
