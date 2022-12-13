#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
/*
name: pfor-sugary-arraysum-scope.c
author: John Rieffel
description: shows how to use pfor correctly ,
            with demonstration of scope
*/


int main(int argc, char *argv[])
{
  int PiVals[10] = {3,1,4,1,5,9,2,6,5,4};
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);
	int globalsum = 0;

  int localmax = 0;

  #pragma omp parallel for num_threads(nthreads) private(localmax) reduction(+:globalsum)
	for (int i = 0; i < 10; i++)
	{
      globalsum+= PiVals[i];
      localmax = PiVals[i] > localmax ? PiVals[i] : localmax;
      printf("max so far on thread %d: %d\n",omp_get_thread_num(),localmax);
	}
printf("global sum is %d\n",globalsum);
//printf("global sum is %d\n",globalprod);
}
