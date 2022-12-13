/* Fire example code - step 1
 * no modifcations yet made
 */

#include <time.h> 
#include <stdio.h>
#include <stdlib.h>

//magic of C - a function that returns a positive number of a > b, and a negative number otherwise.
//requirements of qsort are that the Compare function has to take voids are arguments
//so we cast to int inside function.
int CompareInts(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}
//Use this in your MPI Sorting Code
void PrintArray(int *array, int asize)
{
    for (int i =0; i < asize; i++)
        printf(" %d ", array[i]);
    printf("\n");

}

//Use this in your MPI Sorting Code
void SortMySlice(int *slice, int slicesize)
{
    qsort(slice,slicesize,sizeof(int),CompareInts);
}

//swap two integers
void Swap(int *a, int *b)
{
                int tmp = *a;
                *a=*b;
                *b = tmp;
                return;

}

//Merges to equally sized arrays of integers
// only caring to keep the smallest items across the two arrays
// in myslice
void MergeSlicesKeepSmaller(int *myslice, int mysize, int *otherslice, int othersize)
{
    //it's less fun to do recursively than you might imagine.
    for (int i = 0; i < mysize; i++)
    {
        for (int j = 0; j <= i; j++){
            if (otherslice[j] < myslice[i]) {
                Swap(myslice+i,otherslice+j);
            }
        }
    }

}
int main() {

    int numitems = 9;
    int B[9] = {3,1,4,1,5,9,2,6,5};
    int A[9] = {6,32,5,623,6,234,3,0};
    MergeSlicesKeepSmaller(A,numitems,B,numitems);
    PrintArray(A,numitems);
    PrintArray(B,numitems);
}
