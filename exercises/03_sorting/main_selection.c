/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test the Selection algorithm.
 * @date 01-07-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utility.h"
#include "sorting.h"

#define MAX_SIZE 100000000
#define PRINT_STOP 10000000

int main(int argc, char *argv[]) 
{
    struct timespec b_time, e_time;
    printf("Size\t\tSelection Algorithm\tCorrectness\n");
    printf("----\t\t-------------------\t-----------\n");
    for (size_t i = 256; i < MAX_SIZE; i *= 2) 
    {
        int* a = (int*)malloc(sizeof(int) * i);
        random_fill_array_unsigned_int(a, i, MAX_SIZE);

        clock_gettime(CLOCK_REALTIME, &b_time);
        int val = selection(a, 0, i, i / 3 + 1);
        clock_gettime(CLOCK_REALTIME, &e_time);

        quicksort(a, i, 1);
        int correct = a[i / 3 + 1] == val;

        if (i <= PRINT_STOP)
        {
            printf("%d\t\t%lf\t\t%d\n", i, get_execution_time(b_time, e_time), correct);
        }
        else
        {
            printf("%d\t%lf\t\t%d\n", i, get_execution_time(b_time, e_time), correct);
        }

        free(a);
    }
    return 0;
}
