#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

/*
vectors.c for week 1 bootcamp
author: John Rieffel

*/

//argc is the argument count from the commandline
//argc is always at least 1, because the excutable
//is an argument
//
//each argument is held in a separate string.
//argv is an *array* of strings

double * randomize_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
   vec[index] = rand() % 101;
  }
  return vec;
}

void print_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
    printf("%f ", vec[index]);
}
  printf("\n");
  return;
}

void print_vector_p(double *vec, int size)
{
  double *p;
  double * vec_end = vec+size;
  for (p = vec; p < vec_end; p++)
  {
    printf("%f ", *p);
  }
}

void vector_add(double *v1, double* v2, double *result, int size, int nthreads)
{
  #pragma omp parallel num_threads(nthreads)
  {
    int myid = omp_get_thread_num();
    int threadcount = omp_get_num_threads(); 
    for (int i = myid; i < size; i+=threadcount){
      result[i]+= v1[i]+ v2[i];
    }
  }
}

//return the mean of a vector
double vector_mean(double *v1, int size, int nthreads)
{ 
  int sum = 0;
  double average;
  int numthreads = (size > nthreads) ? nthreads : size; // if our threads are way bigger than size there is no need to use all of them

  #pragma omp parallel num_threads(numthreads)
  {
    int myid = omp_get_thread_num();
    int threadcount = omp_get_num_threads(); 
    for (int i = myid; i < size; i+=threadcount){
      sum += v1[i];
    }
  }
  average = (double) sum / size;
  return average;
}

//return the magnitude of a a vector
// (squareroot of sum of squares )
double vector_mag(double *v1, int size, int nthreads)
{
  double globalsumSquares = 0;
  double localsumSquares = 0;

  int numthreads = (size > nthreads) ? nthreads : size; // if our threads are way bigger than size there is no need to use all of them
  // printf("\nNumthreads: %d Size: %d\n", numthreads, size);
  #pragma omp parallel num_threads(numthreads)
  {
    int myid = omp_get_thread_num();
    int threadcount = omp_get_num_threads(); 
    for (int i = myid ; i < size; i+=threadcount){
      localsumSquares+=v1[i]*v1[i]; // We wanna add all the elements of pi
    }
  }
	#pragma omp critical 
  {
	  globalsumSquares+=localsumSquares;
  }
  return sqrt(globalsumSquares);
}

//normalize a vector, putting result in outv 
void vector_normalize(double *v1, double *outv, int size, int nthreads)
{
  //first a call to vector mag
  double globalmag = vector_mag(v1, size, nthreads);

  //then an omp for loop that divides evertying in the vector by magnitude
  #pragma omp parallel num_threads(nthreads)
  {
    int myid = omp_get_thread_num();
    int threadcount = omp_get_num_threads(); 
    for (int i = myid ; i < size; i+=threadcount){
      outv[i] = (double) (v1[i] / globalmag);
    }
  }
  //warning don't ever omp parallelize loops that call functions that also parallelize 
}

int main(int argc, char *argv[])
{
  int SIZE = 10;
  int nthreads = 1;
  if (argc > 4){
    printf("usage: vectors <procs> <size> or vectors <procs> <size> <seed>\n ");
    exit(1);
  }
  else {
      if (argc > 1)
        nthreads = strtol(argv[1],NULL,10); 
      if (argc > 2)
        SIZE = atoi(argv[2]); //atoi converts a string to an int
      if (argc > 3)
        srand(atoi(argv[3]));
      else
        srand(time(NULL));
  }
  printf("threads: %d, vector size: %d\n",nthreads,SIZE);

  //calloc, unlike malloc, zeros the allocated memory
  double * vector1 =  calloc(SIZE,sizeof(double));
  double * vector2 =  calloc(SIZE,sizeof(double));
  double * normalVector =  calloc(SIZE,sizeof(double)); // our normalized vector holder
  double * vecSum =  calloc(SIZE,sizeof(double)); // our normalized vector holder


  vector1 = randomize_vector(vector1, SIZE);
  vector2 = randomize_vector(vector2, SIZE);
  printf("vector1: ");
  print_vector_p(vector1,SIZE);
  printf("\n");
  printf("vector2: ");
  print_vector_p(vector2,SIZE);

  printf("\n\n=======================\n");
  double mag = vector_mag(vector1, SIZE, nthreads);
  printf("Mag Vector 1: %f", mag);
  printf("\n");
  printf("Normalized Vector 1: ");
  vector_normalize(vector1, normalVector, SIZE, nthreads);
  print_vector_p(normalVector, SIZE);
  printf("\n");
  double magCheck = vector_mag(normalVector, SIZE, nthreads);
  printf("Normalized Vector Mag: %f\n", magCheck);

  // =============================================
  printf("\n\n=======================\n");

  // mean of vector 2
  double mean = vector_mean(vector2, SIZE, nthreads);
  printf("Mean of Vector 2: %f\n", mean);
  printf("\n\n=======================\n");

  // Vector sum
  vector_add(vector1, vector1, vecSum, SIZE, nthreads);
  printf("Sum of Vectors 1 and 2: ");
  print_vector_p(vecSum, SIZE);
  printf("\n");

} 
