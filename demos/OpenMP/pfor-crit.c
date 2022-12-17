#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
  int globalval = 0;
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);
  #pragma omp parallel for num_threads(nthreads)
	for (int i = 0; i < 100000; i++)
	{
		int localval = omp_get_thread_num();
//	  printf("thread %d has ival %d.\n",omp_get_thread_num(),i);
	#pragma omp critical
		globalval += localval;
	}
 printf("global is:%d\n",globalval);
}
