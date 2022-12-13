#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/*
vectors.c for week 1 bootcamp
author: John Rieffel

*/

//argc is the argument count from the commandline
//argc is always at least 1, because the exchjkhjutable
//is an argument
//
//each argument is held in a separate string.
//argv is an *array* of strings

double * randomize_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
   vec[index] = drand48();
  }
  return vec;
}

double * randomize_vector_p(double *vec, int size)
{
  double *p;
  double * vec_end = vec+size;
  // printf("\nCurrent value of *p, %f", *p);
  // printf("\nCurrent value of *vec %f", *vec);

  int INDEX = 0;
  for (p = vec; p < vec_end; p++)
  {
    *p = drand48();
    // printf("\n[%d] Current value of *p,%f", INDEX, *p);  
    // printf("%f", *p);
    INDEX++;
  }
  // printf("\nThe 'vec' we are returning: %p\n", vec); // %p allows pointers
  return vec;
}

double * add_vectors(double * vec1, double * vec2, int size)
{
  double * newVector = calloc(size, sizeof(double));

  if (sizeof(vec1)==sizeof(vec2))
  {
    double * p1; //pointer for vec1
    double * p2; //pointer for vec2
    double * p0; // pointer for newVector

    double * vec_end = vec1+size;

    int INDEX = 0;
    for (p1 = vec1, p2 = vec2, p0 = newVector; p1 < vec_end; p1++, p2++, p0++)
    {
      // printf("[%d] vectors: [vec1: %lf], [vec2: %lf]\n", INDEX, *p1, *p2);
      *p0 = *p1 + *p2; // add

      // printf("[%d] sum: %lf\n\n", INDEX, *p0);
      INDEX++;
    }
  }
  return newVector;
}

double * dot(double * vec1, double * vec2, int size)
{
  double * dotProduct = calloc(size, sizeof(double));

  if (sizeof(vec1)==sizeof(vec2))
  {
    double * p1; //pointer for vec1
    double * p2; //pointer for vec2
    double * p0; // pointer for dotProduct

    double * vec_end = vec1+size;

    int INDEX = 0;
    for (p1 = vec1, p2 = vec2, p0 = dotProduct; p1 < vec_end; p1++, p2++, p0++)
    {
      // printf("[%d] vectors: [vec1: %lf], [vec2: %lf]\n", INDEX, *p1, *p2);
      *p0 = (*p1) * (*p2); // multiply

      // printf("[%d] product: %lf\n\n", INDEX, *p0);
      INDEX++;
    }
  }
  return dotProduct;
}


void print_vector(double *vec, int size)
{
  int index;
  for (index= 0; index< size; index++ ) {
    printf("%f ", vec[index]);
}
}

void print_vector_p(double *vec, int size)
{
  printf("Vector pointer: %p\n", vec);

  double * p;
  double * vec_end = vec+size;
  for (p = vec; p < vec_end; p++)
  {
    printf("%f ", *p);
  }
}

int main(int argc, char *argv[])
{
  int SIZE = 0;

  if ((argc < 2) || (argc > 3)){
    printf("usage: vectors <size> or vectors <size> <seed>\n ");
    exit(1);
  }
  else {
      SIZE = atoi(argv[1]); //atoi converts a string to an int
      printf("size: %d\n\n",SIZE);
      if (argc == 3)
        srand48(atoi(argv[2]));
      else
        srand48(time(NULL));
  }

// start timer
clock_t startTime = clock();

//calloc, unlike malloc, zeros the allocated memory
double * vector1 = calloc(SIZE,sizeof(double));
double * vector2 = calloc(SIZE,sizeof(double));
double * vector3 = calloc(SIZE,sizeof(double));
double * vector4 = calloc(SIZE,sizeof(double));
double * vectorSum = calloc(SIZE, sizeof(double));
double * vectorDot = calloc(SIZE, sizeof(double));


// vector1 = randomize_vector(vector1, 10);
vector1 = randomize_vector(vector1, SIZE);

// print_vector(vector1,10);

vector2 = randomize_vector(vector2, SIZE);
// vector3 = randomize_vector_p(vector1, 5);
vector3 = randomize_vector_p(vector1, SIZE);
vector4 = randomize_vector_p(vector2, SIZE);


printf("VECTOR 1\n");
// print_vector(vector1,10);
print_vector(vector1,SIZE);
printf("\n");

printf("VECTOR 2\n");
print_vector(vector2,SIZE);
printf("\n");

// printf("VECTOR 3:\n");
// print_vector_p(vector3, SIZE);
// printf("\n");
// printf("VECTOR 4:\n");
// print_vector_p(vector4, SIZE);
// printf("\n\n");

// printf("ADDITION:: \n");
vectorSum = add_vectors(vector3, vector4, SIZE);
// print_vector_p(vectorSum, SIZE);
// printf("\n");

// printf("\n\nDOT:: \n");
vectorDot = dot(vector3, vector4, SIZE);
// print_vector_p(vectorDot, SIZE);
// printf("\n\n\n");

clock_t endTime = clock();
double elapsed =  (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
printf("That took %f ms\n",elapsed);

}
