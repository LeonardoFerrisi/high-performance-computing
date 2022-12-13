#include <stdio.h>

int main(int argc, char *argv[])
{
  int A[10] = {3,1,4,1,5,9,2,6,5,4};
  int *pA = A; //this is the same thing as int *pa = &(A[0])
  
  printf("******* INTS *******\n");
  printf("size of int: %lu bytes, size of int*: %lu bytes\n",sizeof(int), sizeof(int *));
  printf("pA is address %p\n",pA);
  printf(" A is address %p\n",A);
  int i ;

  printf("-------starting loop-----\n");
  for (i = 0; i < 10; i++)
    {
      int *addrOfAi = &(A[i]); // reference to A[i]
      printf("addressOfAi is : %p\n",addrOfAi);
      printf("      pA is now: %p\n",pA);
      int arrayval = A[i];  //value at index i
      int pval = *pA;       //also value at index i
      printf("arrayval (A[i]) is: %d, pval (*pA) is %d\n",arrayval,pval);
      pA = pA + 1;  //increment the pointer by one INTEGER ADDRESS
      printf("--- end of iteration %d ---\n",i);
      
    }

  //now an array of characters
  char B[10] = {'3','1','4','1','5','9','2','6','5','4'};
  char *pB = B; //same as above.  points to beginning of B
  pA = (int *)B; //we have to *CAST* pA as an integer pointer (since B is of type char * (sorta))
  printf("******* CHARS *******\n");
  printf("size of char: %lu bytes, size of char *: %lu bytes\n",sizeof(char), sizeof(char *));
  printf("pB has address %p\n",pB);
  printf("pA has address %p\n",pA);
  printf(" B has address %p\n",B);

  int j ;

  printf("-------starting loop-----\n");
  for (j = 0; j < 10; j++)
    {
      char *addrOfBi = &(B[j]); //again, initially all three are the same
      printf("addrOfBi is now: %p\n",addrOfBi);
      printf("      pB is now: %p\n",pB);
      printf("      pA is now: %p\n",pA); //but pA increments by 4 instead of 1!
      char arrayval = B[i];
      char pval = *pB;
      printf("arrayval (B[i]) is: %c, pval (*pB) is %c\n",arrayval,pval);
      pB = pB + 1;
      pA = pA + 1;
      printf("--- end of iteration %d ---\n",j);
      
    }
  

}
