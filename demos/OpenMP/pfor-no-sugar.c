#include <stdio.h>
#include <stdlib.h>
#include <omp.h> 
int main(int argc, char *argv[])
{
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);

  #pragma omp parallel num_threads(nthreads)
{
	int myid = omp_get_thread_num();
	int threadcount = omp_get_num_threads(); //like, super-high threadcount sheets?
	for (int i = myid ; i < 10; i+=threadcount)
	{
		printf("thread %d of %d  has val %d\n",myid, threadcount, i);
	}
} //end of pfor pragma
}
