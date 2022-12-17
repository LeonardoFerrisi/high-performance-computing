#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

/*
omp-pi.c
author: Leonardo Ferrisi

*/

//argc is the argument count from the commandline
//argc is always at least 1, because the excutable
//is an argument
//
//each argument is held in a separate string.
//argv is an *array* of strings

#define PI 3.141592653589793


double calc_pi(int N, int nthreads)
{
    omp_set_num_threads(nthreads);   
    double sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i=0; i < N; i++)
    {
        double dx = (double) 1/N;
        double w = dx;
        double xval = i*dx;
        double h = sqrt(1-(xval*xval));
        sum = sum + w*h;
    }
    double pi = 4*sum;
    return pi;
}


int main(int argc, char *argv[])
{
  int N = 1;
  int nthreads = 1;
  int VERBOSE = 0;
  
  if ( (argc > 3) || (argc < 2) ){
    printf("usage: omp-pi <numThreads> <N> or omp-pi <numThreads> <N> <VERBOSE>\n ");
    exit(1);
  }
  else {
      if (argc > 1)
        nthreads = strtol(argv[1],NULL,10); 
      if (argc > 2)
        N = atoi(argv[2]); //atoi converts a string to an int
      if (argc > 3)
        VERBOSE = atoi(argv[3]);
  }

  double t1 = omp_get_wtime();
  double pi = calc_pi(N, nthreads);
  double t2 = omp_get_wtime();
  double error = ((double) PI) - pi;
  printf("Estimated Pi: %f, Actual: %f, Error: %f, Time Elapsed: [%f]\n", pi, PI, fabs(error), (t2-t1));
}