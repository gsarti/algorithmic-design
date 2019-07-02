/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test sorting algorithms performances.
 * @date 01-07-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utility.h"
#include "sorting.h"

#define MAX_SIZE 20000000
#define INSERTION_STOP 131072
#define PRINT_STOP 10000000
#define COUNTING_STOP 33554432
#define RADIX_STOP 33554432

int main(int argc, char *argv[]) 
{
    struct timespec b_time, e_time;
    double insert_time, quick_time, heap_time, count_time, radix_time, bucket_time;
    printf("Size\t\tInsertion\tQuick\t\tHeap\t\tCount\t\tRadix\t\tBucket\n");
    printf("----\t\t---------\t-----\t\t----\t\t-----\t\t-----\t\t------\n");
    for (size_t i = 256; i < MAX_SIZE; i *= 2) 
    {
        unsigned int ** mat = allocate_matrix_unsigned_int(5, i);
        random_fill_matrix_unsigned_int(mat, 5, i, MAX_SIZE);

        // Matrix of uniformly distributed float values for Bucket sort.
        float ** mat_unif = allocate_matrix(1, i);
        random_fill_matrix_unif(mat_unif, 1, i);

        // Used to validate sorting results.
        int * sorted = (int *)malloc(sizeof(int) * 6);

        if(i <= INSERTION_STOP)
        {
            clock_gettime(CLOCK_REALTIME, &b_time);
            insertion_sort(mat[0], i);
            clock_gettime(CLOCK_REALTIME, &e_time);
            insert_time =  get_execution_time(b_time, e_time);
        }

        clock_gettime(CLOCK_REALTIME, &b_time);
        quicksort(mat[1], i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        quick_time =  get_execution_time(b_time, e_time);

        clock_gettime(CLOCK_REALTIME, &b_time);
        heapsort(mat[2], i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        heap_time =  get_execution_time(b_time, e_time);

        if(i <= COUNTING_STOP)
        {
            clock_gettime(CLOCK_REALTIME, &b_time);
            counting_sort(mat[3], i, MAX_SIZE);
            clock_gettime(CLOCK_REALTIME, &e_time);
            count_time =  get_execution_time(b_time, e_time);
        }

        if(i <= RADIX_STOP)
        {
            clock_gettime(CLOCK_REALTIME, &b_time);
            radix_sort(mat[4], i, max_array_int(mat[4], i));
            clock_gettime(CLOCK_REALTIME, &e_time);
            radix_time =  get_execution_time(b_time, e_time);
        }

        clock_gettime(CLOCK_REALTIME, &b_time);
        bucket_sort(mat_unif[0], i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        bucket_time =  get_execution_time(b_time, e_time);

        if(i <= INSERTION_STOP)
        {
            printf("%d\t\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
                    i, insert_time, quick_time, heap_time, count_time, 
                    radix_time, bucket_time);
        }
        else if (i <= PRINT_STOP)
        {
            printf("%d\t\t\t\t%lf\t%lf\t%lf\t%lf\t%lf\n",
                    i, quick_time, heap_time, count_time, 
                    radix_time, bucket_time);
        }
        else if (i <= COUNTING_STOP)
        {
            printf("%d\t\t\t%lf\t%lf\t%lf\t%lf\t%lf\n",
                    i, quick_time, heap_time, count_time, 
                    radix_time, bucket_time);
        }
        else
        {
            printf("%d\t\t\t%lf\t%lf\n", i, quick_time, heap_time);
        }

        deallocate_matrix((void **)mat, 5);
        deallocate_matrix((void **)mat_unif, 1);
        free(sorted);
    }
    return 0;
}
