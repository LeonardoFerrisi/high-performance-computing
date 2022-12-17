#include <stdio.h>
#include <time.h>
#include <omp.h>

//tasks.c
// a brief demo of task sections in OMP
int main(int argc, char *argv[])
{

  int i;
#pragma omp parallel sections num_threads(2) private(i)
  {
    #pragma omp section 
    {
      for (i = 0; i < 100; i++)
	      printf("rubbing belly on thread %d of %d\n",omp_get_thread_num(),omp_get_num_threads());
    }
    #pragma omp section 
    {
      for (i = 0; i < 100; i++)
	      printf("patting head on thread %d of %d\n",omp_get_thread_num(),omp_get_num_threads());
    }
  }
}
