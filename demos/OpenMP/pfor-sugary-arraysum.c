#include <stdio.h>

/*
name: pfor-sugary-arraysum.c
author: John Rieffel
description: shows how to use pfor correctly ,
            with stub to show a reduction operator.
*/


int main(int argc, char *argv[])
{
  int PiVals[10] = {3,1,4,1,5,9,2,6,5,4};
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);
	int globalsum = 0;


  #pragma omp parallel for num_threads(nthreads) reduction(+:globalsum)
	for (int i = 0; i < 10; i++)
	{
      globalsum+= PiVals[i];
	}
printf("global sum is %d\n",globalsum);
//printf("global sum is %d\n",globalprod);
}
