/*
name: hello2.c
author: John Rieffel
description: the simple form of OpenMP-based hello world.
              this demonstrates what a parallel block looks like.
              With informative printfs

instructions: compile with gcc -fopenmp
*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h> 

int main(int argc, char *argv[])
{
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);

  printf("#### BEGIN PARALLELIZED BLOCK###\n");
  #pragma omp parallel num_threads(nthreads)
	{
	  printf("Hello, world, from thread %d of %d.\n",omp_get_thread_num(), omp_get_num_threads());
	  printf("Look, %d,  we can specify blocks with curly braces!\n",omp_get_thread_num());
	}
  printf("#### END PARALLELIZED BLOCK###\n");
  printf("and now our parallel block is done\n");
}
