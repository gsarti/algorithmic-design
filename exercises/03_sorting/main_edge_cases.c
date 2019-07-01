/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test best/worst case for Insertion and Quicksort.
 * @date 01-07-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utility.h"
#include "sorting.h"

#define MAX_SIZE 100000000
#define INSERTION_STOP 131072
#define PRINT_STOP 10000000

int main(int argc, char *argv[]) 
{
    struct timespec b_time, e_time;
    printf("Size\t\tInsertion\tIns. Best\tIns. Worst\tQuick\t\tQuick Best\tQuick Worst\n");
    printf("----\t\t---------\t---------\t----------\t-----\t\t----------\t-----------\n");
    for (size_t i = 256; i < MAX_SIZE; i *= 2) 
    {
        unsigned int ** mat = allocate_matrix_unsigned_int(6, i);
        random_fill_matrix_unsigned_int(mat, 6, i, MAX_SIZE);
        sequential_fill_array_int(mat[1], i, 0);
        sequential_fill_array_int(mat[2], i, 1);
        sequential_fill_array_int(mat[4], i, 0);
        sequential_fill_array_int(mat[5], i, 1);

        double i_time, ib_time, iw_time, q_time, qb_time, qw_time;
        
        if(i <= INSERTION_STOP)
        {
            clock_gettime(CLOCK_REALTIME, &b_time);
            insertion_sort(mat[0], i);
            clock_gettime(CLOCK_REALTIME, &e_time);
            i_time =  get_execution_time(b_time, e_time);
        }

        clock_gettime(CLOCK_REALTIME, &b_time);
        insertion_sort(mat[1], i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        ib_time =  get_execution_time(b_time, e_time);

        if(i <= INSERTION_STOP)
        {
            clock_gettime(CLOCK_REALTIME, &b_time);
            insertion_sort(mat[2], i);
            clock_gettime(CLOCK_REALTIME, &e_time);
            iw_time =  get_execution_time(b_time, e_time);
        }

        clock_gettime(CLOCK_REALTIME, &b_time);
        quicksort(mat[3], i, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        q_time =  get_execution_time(b_time, e_time);

        clock_gettime(CLOCK_REALTIME, &b_time);
        quicksort(mat[4], i, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        qb_time =  get_execution_time(b_time, e_time);

        clock_gettime(CLOCK_REALTIME, &b_time);
        quicksort(mat[5], i, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        qw_time =  get_execution_time(b_time, e_time);

        if(i <= INSERTION_STOP)
        {
            printf("%d\t\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",
                    i, i_time, ib_time, iw_time, q_time,
                    qb_time, qw_time);
        }
        else if (i <= PRINT_STOP)
        {
            printf("%d\t\t\t\t%lf\t\t\t%lf\t%lf\t%lf\n",
                i, ib_time, q_time, qb_time, qw_time);
        }
        else
        {
            printf("%d\t\t\t%lf\t\t\t%lf\t%lf\t%lf\n",
                i, ib_time, q_time, qb_time, qw_time);
        }
        
        deallocate_matrix((void **)mat, 6);
    }
    return 0;
}
