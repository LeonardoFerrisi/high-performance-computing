#include <stdio.h>
#include <time.h>
#include <math.h>
#include <limits.h>
// for boolean
#include <stdbool.h>
#include <math.h>

/*
Returns the number of divisors for a big number
*/
int main(int argc, char *argv[])
{

  unsigned long long bignumber = 3890609;

  if (argc > 1)
  {
    bignumber = (atoi(argv[1]));
  }

  // printf ("sizeof unsigned long: %lu",sizeof(unsigned long));
  // printf ("sizeof unsigned long long: %lu",sizeof(unsigned long long));

  unsigned long i;
  unsigned int num = 0;
  bool isPrime = false;
  char b = 43;

  clock_t startTime = clock();
  // for (i = 3; i < ULLONG_MAX; i++) // Basicially runs infinately

  for (i = 3; i < bignumber; i += 2) // increments by two
  {
    if ((bignumber % i) == 0)
    {
      // printf("I found %lu\n",i); // Alot like python ( % ) % input
      // break;
      num += 1;
    }

    if (i == sqrt(bignumber))
    {
      printf("Reached square root! Was: %lu", i);
      break;
    }
    // Attempt at a loading bar, only ever displays when finished :(
    // if (i % (bignumber / 2) == 0)
    // {
    //   printf("%c", b);
    // }
  }
  printf("\n");
  // check if is prime
  if (num == 0) // Because i starts at 1 and ends before bignumber, the only divisors will never be looked at if it is prime
  {
    isPrime = true;
  }

  printf("Total amount of divisors %d\n", num);
  printf("Is Prime: %d [0 = false, 1 = true]\n", isPrime);

  clock_t endTime = clock();
  double elapsed = (double)(endTime - startTime) * 1000.0 / CLOCKS_PER_SEC;
  printf("that took %f ms\n", elapsed);
  return num;
}
