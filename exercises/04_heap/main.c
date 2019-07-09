/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test heap building execution time.
 * @date 30-06-2019
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "heap.h"
#include "../utility.h"

#define ITERATIONS 10

int main()
{
    const size_t heap_size = 1E7;
    unsigned int ** mat = allocate_matrix_unsigned_int(ITERATIONS, heap_size);
    printf("Generating the value matrix of size %d...\n", heap_size);
    random_fill_matrix_unsigned_int(mat, ITERATIONS, heap_size, heap_size);

    struct timespec b_time, e_time;
    printf("Iteration\tTime (s)\n");

    for (size_t i = 0; i < ITERATIONS; i++)
    {
        clock_gettime(CLOCK_REALTIME, &b_time);
        BinaryHeap H = build_heap(mat[i], heap_size, leq);
        clock_gettime(CLOCK_REALTIME, &e_time);
        printf("%d\t\t%lf\n", i+1, get_execution_time(b_time, e_time));
    }
    deallocate_matrix((void**)mat, ITERATIONS);
}