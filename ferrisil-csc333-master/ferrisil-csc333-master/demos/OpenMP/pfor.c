#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
/*
name: pfor.c
author: John Rieffel
description: shows how to use a parallel for pragma
              and demonstrates how iterations are partitioned
              among threads
*/

int main(int argc, char *argv[])
{
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);
  #pragma omp parallel for num_threads(nthreads) schedule(static,4)
	for (int i = 0; i < 100; i++)
	{
    //note, each thread has a private copy of i
	  //printf("thread %d has ival %d at address %p.\n",omp_get_thread_num(),i,&i);
	  printf("thread %d has ival %d\n",omp_get_thread_num(),i);
	}
}
