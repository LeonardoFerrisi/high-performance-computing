#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[])
{
  int ROWS = 0;
  int COLS = 0;
  // THIS WILL BE YOUR RANDOM SEED
  // YES IT IS NON-RANDOM - Read the lab!
  unsigned short xi[3] = {1,9,99};
  double somenum = erand48(xi);

  int nthreads = 1;
  if (argc > 1){
    nthreads = strtol(argv[1],NULL,10);
  }

  if (argc != 4){
    printf("usage: matrices <nthreads> <rows> <cols>\n ");
    exit(1);
  }

  else{
      ROWS = atoi(argv[2]);
      COLS = atoi(argv[3]);
      printf("Rows: %d, Cols: %d\n",ROWS,COLS);
  } 

  //double MAT[][] = calloc(ROWS*COLS,sizeof(double));
  //double MAT[ROWS][COLS];
  double * MAT =  calloc(ROWS*COLS,sizeof(double));
  double * MAT1 =  calloc(ROWS*COLS,sizeof(double));

  // double t1 = omp_get_wtime();
  randomizeMatrix(MAT, ROWS, COLS);
  randomizeMatrix(MAT1, ROWS, COLS);
  // double t2 = omp_get_wtime();

  // printTwoDArray(MAT, ROWS, COLS);
  // printf("\n");
  // printTwoDArray(MAT1, ROWS, COLS);

  double * SUM =  calloc(ROWS*COLS,sizeof(double));

  double * tM =  calloc(ROWS*COLS,sizeof(double));

  double t1 = omp_get_wtime();
  // addMatricies(SUM, MAT, MAT1, ROWS, COLS, nthreads, 100);
  transposeMatricies(MAT, ROWS, COLS, tM, nthreads, 100);
  double t2 = omp_get_wtime();

  printf("\n");

  // printTwoDArray(tM, ROWS, COLS);
  printf("\n");
  // printTwoDArray(SUM, ROWS, COLS);


  printf("Time Elapsed: %f\n", (t2 - t1)*1000);
}

void randomizeMatrix(double *arr, int rows, int cols){
  srand(time(NULL));
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++)
	  {
      arr[i * cols + j] = rand() % 101;
	    // printf("%d, %d\n",i ,j);
	  }
  }
}

void printTwoDArray(double *arr, int rows, int cols){
  for (int i = 0; i < rows; i++ ) {
    for (int j = 0; j < cols; j++) {
        printf("%f ",arr[i*cols + j]);
    }
    printf("\n");
  }
}

void addMatricies(double *sum, double *arr1, double *arr2, int rows, int cols, int THREADS, int CHUNK){
  /*
  * Adds two matricies together
  */
  #pragma omp parallel for schedule(static, CHUNK) num_threads(THREADS) private(j) 
  // #pragma omp parallel for schedule(dynamic, CHUNK) num_threads(THREADS)
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++)
	  {
      sum[i * cols + j] = arr1[i*cols + j] + arr2[i*cols + j];
	  }
  }
}

void transposeMatricies(double *arr1, int rows, int cols, double *rm, int THREADS, int CHUNK){
    /*
  * Swaps rows and colums
  */
  // #pragma omp parallel for schedule(static, CHUNK) num_threads(THREADS)
  #pragma omp parallel for schedule(dynamic, CHUNK) num_threads(THREADS) private(j) 
  for (int i=0; i<rows; i++){
    for (int j=0; j<cols; j++)
	  {
      rm[j * cols + i] = arr1[i * cols + j];
	  }
  }
}

//free(MAT); //don't FREE! C99 takes care of it if allocated like this
//(instead of via malloc)

