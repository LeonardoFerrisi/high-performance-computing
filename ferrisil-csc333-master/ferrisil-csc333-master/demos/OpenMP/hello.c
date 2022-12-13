/*
name: hello.c
author: John Rieffel
description: the simplest form of OpenMP-based hello world.
instructions: compile with gcc -fopenmp
*/
#include <stdio.h>
#include <omp.h> //this line will choke if openMP is not installed

int main(void)
{
  //this will be ignored by non-supportive compilers
  //otherwise, launch a default number of threads.
  #pragma omp parallel
  printf("Hello, world.\n");
  return 0;
}
