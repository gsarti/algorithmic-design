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
#define MAX_SIZE 2048

int main(int argc, char *argv[]) 
{
    float **C0 = allocate_matrix(MAX_SIZE,MAX_SIZE);
    float **C1 = allocate_matrix(MAX_SIZE, MAX_SIZE);
    float **C2 = allocate_matrix(MAX_SIZE, MAX_SIZE);
    float **A = allocate_matrix(MAX_SIZE, MAX_SIZE);
    float **B = allocate_matrix(MAX_SIZE, MAX_SIZE);

    random_fill_matrix(A, MAX_SIZE, MAX_SIZE, MAX_MAT_VALUE);
    random_fill_matrix(B, MAX_SIZE, MAX_SIZE, MAX_MAT_VALUE);

    struct timespec b_time, e_time;
    double naive_time, strassen_time, opt_time;
    int correctness = 0;

    printf("Size\tNaive\t\tStrassen\tStrassen Opt.\tCorrectness\n");
    printf("----\t-----\t\t--------\t-------------\t-----------\n");    

    for (size_t i = 2; i <= MAX_SIZE; i *= 2) 
    {
        clock_gettime(CLOCK_REALTIME, &b_time);
        naive_matrix_mult(C0, A, B, i, i, i, i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        naive_time = get_execution_time(b_time, e_time);

        clock_gettime(CLOCK_REALTIME, &b_time);
        strassen(C1, A, B, i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        strassen_time = get_execution_time(b_time, e_time);

        clock_gettime(CLOCK_REALTIME, &b_time);
        strassen_opt(C2, A, B, i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        opt_time = get_execution_time(b_time, e_time);

        correctness = same_matrix(C0, i, i, C1, i, i) &&
                      same_matrix(C1, i, i, C2, i, i);

        printf("%d\t%lf\t%lf\t%lf\t%d\n", i, naive_time, strassen_time, opt_time, correctness);
    }

    deallocate_matrix((void **)C0,MAX_SIZE);
    deallocate_matrix((void **)C1,MAX_SIZE);
    deallocate_matrix((void **)C2,MAX_SIZE);
    deallocate_matrix((void **)A,MAX_SIZE);
    deallocate_matrix((void **)B,MAX_SIZE);

    return 0;
}
