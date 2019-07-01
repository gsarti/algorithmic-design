/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test optimized Strassen implementation performances.
 * @date 30-06-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utility.h"
#include "strassen.h"
#include "homework.h"

#define MAX_MAT_VALUE 25

int main(int argc, char *argv[]) 
{
    const size_t n=1<<11;

    float **C0=allocate_matrix(n,n);
    float **C1=allocate_matrix(n,n);
    float **C2=allocate_matrix(n,n);
    float **A=allocate_matrix(n,n);
    float **B=allocate_matrix(n,n);

    srand(10);

    random_fill_matrix(A, n, n, MAX_MAT_VALUE);
    random_fill_matrix(B, n, n, MAX_MAT_VALUE);

    struct timespec b_time, e_time;

    printf("SIZE |  NAIVE (s)   |   STRASSEN (s) | " \
           "STRASSEN_OPT (s) | ALL_EQUAL\n");

    for (size_t i=1; i<=n; i*=2) 
    {
        printf("%ld", i);

        clock_gettime(CLOCK_REALTIME, &b_time);
        naive_matrix_mult(C0, A, B, i, i, i, i);
        clock_gettime(CLOCK_REALTIME, &e_time);

        printf("\t%lf", get_execution_time(b_time, e_time));

        clock_gettime(CLOCK_REALTIME, &b_time);
        strassen(C1, A, B, i);
        clock_gettime(CLOCK_REALTIME, &e_time);

        printf("\t%lf", get_execution_time(b_time, e_time));

        clock_gettime(CLOCK_REALTIME, &b_time);
        strassen_opt(C2, A, B, i);
        clock_gettime(CLOCK_REALTIME, &e_time);

        printf("\t%lf", get_execution_time(b_time, e_time));
        
        printf("\t  %d", same_matrix(C0, i, i, C1, i, i));
        printf("\t%d\n", same_matrix(C1, i, i, C2, i, i));
    }

    deallocate_matrix((void **)C0,n);
    deallocate_matrix((void **)C1,n);
    deallocate_matrix((void **)C2,n);
    deallocate_matrix((void **)A,n);
    deallocate_matrix((void **)B,n);

    return 0;
}
