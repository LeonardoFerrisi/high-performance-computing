/*
name: hello-better.c
author: John Rieffel
description: a form of OpenMP-based hello world.
             that uses #ifdefs to ensure
             cross compiling without openmp
instructions: compile with gcc -fopenmp
*/
#include <stdio.h>
#ifdef _OPENMP  //if OpenMP is installed, this evals to True
#include <omp.h>
#endif   //please don't forget this!

int main(void)
{
  #pragma omp parallel
    printf("Hello, world.\n");
  return 0;
}
