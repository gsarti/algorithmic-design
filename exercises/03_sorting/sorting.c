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

void insertion_sort_int(int * array, size_t size)
{
    size_t j;
    for(size_t i = 1; i < size; i++)
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

void quicksort(int * array, size_t size, int central_pivot)
{
    quicksort_rec(array, 0, size, central_pivot);
}

/* HEAPSORT */

void heapsort(int * array, size_t size)
{
    BinaryHeap H = build_heap(array, size, geq);

    for (int i = size - 1; i > 0; i--)
    {
        array[i] = remove_min(H);
    }
}

/* COUNTING SORT */

void counting_sort(int * array, size_t size, size_t bound)
{
    int * c = (int *)calloc(bound, sizeof(int));
    int * res = (int *)malloc(sizeof(int) * size);

    for (int i = 0; i < size; i++)
        c[array[i]]++;
    
    for (int j = 1; j < bound; j++)
        c[j] += c[j - 1];
    
    for (int i = size - 1; i >= 0; i--) 
    {
        res[c[array[i]] - 1] = array[i];
        c[array[i]]--;
    }

    free(c);
}



