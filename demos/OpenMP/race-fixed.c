/*
name: race-fixed.c
author: John Rieffel
description: demonstrates how to resolve a race condition
						  using the critical pragma
instructions: compile with gcc -fopenmp
*/

#include <stdio.h>
#include <omp.h>

int main(void)
{

	int x = 0;
	int globalsum = 0;

  #pragma omp parallel
	{
		//above this line we're doing all sorts-of threadsafe and independent stuff
   		//but we want this line below to be atomized
		#pragma omp critical
		globalsum += 	omp_get_thread_num();
	}
  printf("global sum = %d\n",globalsum);

  return 0;
}
