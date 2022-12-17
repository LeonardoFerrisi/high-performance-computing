#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/*
name: pfor-no-sugar-arraysum-reduce.c
author: John Rieffel
description: shows how to use a reduction operator.  In this case, reducing globalsum
            with the + operator
            and with stubs to show reduction with multiplication too
*/


int main(int argc, char *argv[])
{
  int PiVals[10] = {3,1,4,1,5,9,2,6,5,4};
  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);
	int globalsum = 0;
  int globalprod = 1;

  #pragma omp parallel num_threads(nthreads) reduction(*:globalprod)// reduction(*:globalprod)
{
	int myid = omp_get_thread_num();
	int threadcount = omp_get_num_threads(); //like, super-high threadcount sheets?
	for (int i = myid ; i < 10; i+=threadcount)
	{
      //look, I have replaced the local variable
      // with a reduction variable!
      //globalsum *= PiVals[i];
      //globalprod *= PiVals[i];
      globalprod += PiVals[i];

    printf("I am thread %d and my val is %d (sum %d)\n",myid,PiVals[i],globalprod);
	}
} //end of pfor pragma

//printf("global sum is %d\n",globalsum);
printf("global sum is %d\n",globalprod);
}
