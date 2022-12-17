#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
/*
name: pfor-sugary-arraysum.c
author: John Rieffel
description: shows how to use pfor correctly ,
            with stub to show a reduction operator.
*/

//compile with make arraysum-omp-with-args

int main(int argc, char *argv[])
{

  int array_size = 100;
  int bigArray = malloc(sizeof(int)*array_size);
  int PiVals[10] = {3,1,4,1,5,9,2,6,5,4};
  int nthreads = 1;
  int chunksize = 1;
  int sched = 0; // 0 = static, 1 = dynamic
  omp_sched_t schedule_type;

  // usage: arraysum-omp-with-args <threads> <chunksize> <schedule type>
  // where schedule type is 0 (static) or 1 (dynamic)
  if (argc > 1)
	  nthreads = strtol(argv[1],NULL,10);
  if (argc > 2)
    chunksize = atoi(argv[2]);
  if (argc > 3)
    sched = atoi(argv[3]);
	int globalsum = 0;

  for (int i = 0; i < array_size; i++)
  {
     bigArray[i] = rand()%10;
  }

  if (sched == 0){
    printf("static %d\n",chunksize);
    //schedule_type = omp_sched_static;
    omp_set_schedule(omp_sched_static,chunksize);
  }
  else
  {
    printf("dynamic %d\n",chunksize);
    //schedule_type = omp_sched_dynamic;
    omp_set_schedule(omp_sched_dynamic,chunksize);
  }


//using runtime schedule allows us to use omp_set_schedule above
  #pragma omp parallel for num_threads(nthreads) reduction(+:globalsum) schedule(runtime) 
	for (int i = 0; i < array_size; i++)
	{
    printf("thread: %d %d\n", omp_get_thread_num(),i);
      globalsum+= bigArray[i];
	}
printf("global sum is %d\n",globalsum);
//printf("global sum is %d\n",globalprod);
}
