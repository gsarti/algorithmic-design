/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Sorting methods - Source
 * @date 29-06-2019
 */
#include <math.h>

#include "sorting.h"
#include "../utility.h"
#include "../04_heap/heap.h"
#include "vector.h"

/* INSERTION SORT */

void insertion_sort(int * array, size_t size)
{
    size_t j;
    for(size_t i = 1; i < size; i++)
    {
        j = i;
        while (j > 0 && array[j] < array[j-1])
        {
            swap_int(&array[j-1], &array[j]);
            j--;
        }
    }
}

void insertion_sort_float(float * array, size_t start, size_t size)
{
    size_t j;
    for(size_t i = start + 1; i < size; i++)
    {
        j = i;
        while (j > start && array[j] < array[j-1])
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
        while (j > start && array[j] < array[j-1])
        {
            swap_int(&array[j-1], &array[j]);
            j--;
        }
    }
}

void insertion_sort_vector(Vector * v)
{
    if (v->root == NULL || v->root->next == NULL)
    {
        return;
    }
    Node * temp1 = v->root->next;
    while(temp1 != NULL)
    {
        float val = temp1->val;
        int found = 0;
        Node * temp2 = v->root;
        while (temp2 != temp1)
        {
            if(temp2->val > temp1->val && !found)
            {
                val = temp2->val;
                temp2->val = temp1->val;
                found = 1;
            }
            else
            {
                if(found)
                {
                    swap(&(val), &(temp2->val));
                }
            }
            temp2 = temp2->next;
        }
        temp2->val = val;
        temp1 = temp1->next;
    }
}


/* QUICKSORT */

int partition(int * array, size_t low, size_t high, size_t pivot_idx)
{
    size_t pivot = array[pivot_idx];
    int i = low - 1;
    int j = high + 1;

    while(1)
    {
        do
        {
            ++i;
        } while (array[i] < pivot);

        do
        {
            j--;
        } while (array[j] > pivot);
        
        if (i >= j)
        {
            return j;
        }
        
        swap_int(&array[i], &array[j]);
    }
}

void quicksort_rec(int * array, size_t low, size_t high, size_t central)
{
    if(low < high)
    {
        int pivot = central ? partition(array, low, high, (high + low) / 2) : partition(array, low, high, low);
        quicksort_rec(array, low, pivot, central);
        quicksort_rec(array, pivot + 1, high, central);
    }
}

void quicksort(int * array, size_t size, size_t central)
{
    quicksort_rec(array, 0, size - 1, central);
}

/* HEAPSORT */

void heapsort(int * array, size_t size)
{
    BinaryHeap H = build_heap(array, size, geq);
    for (int i = size - 1; i >= 1; i--)
    {
        array[i] = remove_min(&H);
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

    copy_array_int(array, res, size);
    free(c);
    free(res);
}

/* RADIX SORT */

void radix_sort(int * array, size_t size, size_t bound)
{
    int max = max_array_int(array, size);
    for (size_t i = 1; max / i > 0; i *= 10)
    {
        int * c = (int *)calloc(10, sizeof(int));
        int * res = (int *)malloc(sizeof(int) * size);

        for (size_t j = 0; j < size; j++)
        {
            c[(array[j] / i) % 10]++;
        }
        for (int j = 1; j < 10; j++)
        {
            c[j] += c[j - 1];
        }
        for (int j = size - 1; j >= 0; j--) 
        {
            res[c[(array[j] / i) % 10] - 1] = array[j];
            c[(array[j] / i) % 10]--;
        }
        copy_array_int(array, res, size);
        free(c);
        free(res);
    }
}

/* BUCKET SORT */

void bucket_sort(float * array, size_t size)
{
    Vector * B = build_bucket(size);

    for (size_t i = 0; i < size; i++)
    {
        append(&B[(int)(array[i] * size)], array[i]);
    }
    for (size_t i = 0; i < size; i++)
    {
        insertion_sort_vector(&B[i]);
    }
    int idx = 0;
    for(size_t i = 0; i < size; i++)
	{
		for(size_t j = 0; j < B[i].length; j++)
		{
            array[idx] = get_val(B[i], j);
            idx++;
		}
    }
	free_bucket(B, size);  
}

/* SELECT ALGORITHM */

int partition_balanced(int * array, size_t low, size_t high, size_t pivot)
{
    swap_int(&array[low], &array[pivot]);
    int i = low + 1;
    int j = high - 1;
    pivot = low;
    int side = 1;

    while(i <= j)
    {
        if (array[i] == array[pivot])
        {
            side = !side;
        }
        if(array[i] > array[pivot] || array[i] == array[pivot] && !side)
        {
            swap_int(&array[i], &array[j]);
            --j;
        }
        else
        {
            i++;
        }
    }
    swap_int(&array[pivot], &array[j]);
    return j;
}

int select_pivot(int * array, size_t low, size_t high)
{
    // If the array length is small, pivot is selected
    // using insertion sort on the whole length.
    if(high - low < 5)
    {
        insertion_sort_int(array, low, high);
        return (low + high) / 2;
    }

    // Number of chunks with optimal chunk size
    int chunks = (high - low) / 5 + 1;

    for (size_t i = 0; i < chunks; i++)
    {
        insertion_sort_int(array, 5 * i + low, MIN(5 * i + low + 4, high));
    }
    for (size_t i = 0; i < chunks; i++)
    {
        swap_int(&array[low + i], &array[MIN(5 * i + low + 2, high - 1)]);
    }
    return select_pivot(array, low, low + chunks);
}

int selection(int * array, size_t low, size_t high, size_t i)
{
    int j = select_pivot(array, low, high);
    int k = partition_balanced(array, low, high, j);
    
    if(i == k)
    {
        return array[k];
    }
    if(i < k)
    {
        return selection(array, low, k, i);
    }
    return selection(array, k + 1, high, i);
}




