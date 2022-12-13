#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// this is good
// because each thread has its own
// unique special little snowflake
// of a private random seed
// that is updated every loop
int main(int argc, char *argv[])
{

  int nthreads = 1;
  if (argc > 1)
	nthreads = strtol(argv[1],NULL,10);

//srand(time(NULL));

int H = 10;
int W = 10;
double m[H][W];
int i,j;
for (i = 0; i < H; ++i)
	{
	for (j = 0; j < W; ++j)
	{
		m[i][j] = 0.0;
//		printf("%f\n",m[i][j];

	}
}
#pragma omp parallel num_threads(nthreads) private(j)
{
unsigned short xi[3] = {1,9,omp_get_thread_num()};

#pragma omp for
for (i = 0; i < H; ++i)
	{
	for (j = 0; j < W; ++j)
	{
		m[i][j] = erand48(xi);
//		printf("%f\n",m[i][j];

	}
	}
}
for ( i = 0; i < H; ++i)
	{
	for (j = 0; j < W; ++j)
		printf("%lf ",m[i][j]);
	printf("\n");
}

}
