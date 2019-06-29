#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

void swap(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int * A, size_t low, size_t high, size_t pivot)
{
    swap(&A[low], &A[pivot]);
    int i = low + 1;
    int j = high - 1;

    while(i <= j)
    {
        if(A[i] > A[low])
        {
            swap(&A[i], &A[j]);
            --j;
        }
        else
        {
            ++i;
        }
    }
    swap(&A[low], &A[j]);
    return j;
}