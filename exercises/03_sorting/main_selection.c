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
    printf("Size\t\tSelection Algorithm\n");
    printf("----\t\t-------------------\n");
    for (size_t i = 256; i < MAX_SIZE; i *= 2) 
    {
        int* a = (int*)malloc(sizeof(int) * i);
        random_fill_array_unsigned_int(a, i, MAX_SIZE);

        clock_gettime(CLOCK_REALTIME, &b_time);
        selection(a, 0, i - 1, i / 3 + 1);
        clock_gettime(CLOCK_REALTIME, &e_time);

        if (i <= PRINT_STOP)
        {
            printf("%d\t\t%lf\n", i, get_execution_time(b_time, e_time));
        }
        else
        {
            printf("%d\t%lf\n", i, get_execution_time(b_time, e_time));
        }

        free(a);
    }
    return 0;
}
