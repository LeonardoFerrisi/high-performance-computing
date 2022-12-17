/*
name: scoping.c
author: John Rieffel
description: demonstrates the scope of variables declared
						 before the parallel pragma (shared)
						 and after the parallel pragma (private)
instructions: compile with gcc -fopenmp
*/
#include <stdio.h>
#include <omp.h>

int main(void)
{

	int x = 0; //this will be a shared variable
	int j;

  #pragma omp parallel
	{
		int y = omp_get_thread_num(); //this will be a private variable
		//variable x should have the same value and address
		printf("thread %d variable x at address %p has val %d\n",omp_get_thread_num(),&x,x);
		//variable y should have a different value and address
		printf("thread %d variable y at address %p has val %d\n",omp_get_thread_num(),&y,y);


	}

  return 0;
}
