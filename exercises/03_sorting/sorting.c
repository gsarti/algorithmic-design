/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Sorting methods - Source
 * @date 29-06-2019
 */

#include "sorting.h"
#include "../utility.h"
#include "../04_heap/heap.h"

/* INSERTION SORT */

void insertion_sort(float * array, size_t start, size_t size)
{
    size_t j;
    for(size_t i = start + 1; i < size; i++)
    {
        j = i;
        while (j > 1 && array[j] < array[j-1])
        {
            swap(&array[j-1], &array[j]);
            j--;
        }
    }
}

void insertion_sort_int(int * array, size_t start, size_t size)
{
    size_t j;
    for(size_t i = start + 1; i < size; i++)
    {
        j = i;
        while (j > 1 && array[j] < array[j-1])
        {
            swap_int(&array[j-1], &array[j]);
            j--;
        }
    }
}

/* QUICKSORT */

int partition(int * A, size_t low, size_t high, size_t pivot)
{
    swap_int(&A[low], &A[pivot]);
    int i = low + 1;
    int j = high - 1;

    while(i <= j)
    {
        if(A[i] > A[low])
        {
            swap_int(&A[i], &A[j]);
            --j;
        }
        else
        {
            ++i;
        }
    }
    swap_int(&A[low], &A[j]);
    return j;
}

void quicksort_rec(int * A, size_t low, size_t high, int central_pivot)
{
    if(low < high)
    {
        int pivot = central_pivot ?
                    partition(A, low, high, (low + high) / 2) :
                    partition(A, low, high, low);
        quicksort_rec(A, low, pivot, central_pivot);
        low = pivot + 1;
    }
}

void quicksort(int * array, size_t start, size_t size, int central_pivot)
{
    quicksort_rec(array, start, size, central_pivot);
}




