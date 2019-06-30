/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Sorting methods - Source
 * @date 29-06-2019
 */

#include "sorting.h"
#include "../utility.h"
#include "../04_heaps/heap.h"

/* INSERTION SORT */

void insertion_sort(int * array, size_t size)
{
    size_t j = 0;
    for(size_t i = 1; i < size; i++)
    {
        j = i;
        while (j > 1 && array[j] < array[j-1])
        {
            swap(&array[j-1], &array[j]);
            --j;
        }
    }
}

/* QUICKSORT */

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

void quicksort_rec(int * A, size_t low, size_t high)
{
    if(low < high)
    {
        int pivot = partition(A, low, high, low);
        quicksort_rec(A, low, pivot);
        low = pivot + 1;
    }
}

void quicksort(int * array, size_t size)
{
    quicksort_rec(array, 0, size);
}




