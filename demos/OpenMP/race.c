/*
name: race.c
author: John Rieffel
description: demonstrates race conditions
						on shared variables within parallel blocks.
						 When run miltiple times, should produce different
						 results.
instructions: compile with gcc -fopenmp
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  int nthreads = 1;
  if (argc > 1)
        nthreads = strtol(argv[1],NULL,10);

	int x = 0;
	int globalsum = 0;

  // globalsum += 1
  // globalsum = globalsum + 1
  //
  // lw $s1 0($t0)
  // add $s1 $s1 1
  // sw $s1 0($s0)

  #pragma omp parallel num_threads(nthreads)
	{
		globalsum += 	omp_get_thread_num();
	}
  printf("global sum = %d\n",globalsum);

  return 0;
}
