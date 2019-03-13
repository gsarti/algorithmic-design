#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "strassen.h"
#include "homework.h"

#define MAX_ELEM_VALUE 25

void randomly_fill_matrix(float **A, const size_t A_rows, const size_t A_cols)
{
   for (size_t i=0; i< A_rows; i++) {
     for (size_t j=0; j< A_cols; j++) {
   	   A[i][j]=rand()%(2*MAX_ELEM_VALUE)-MAX_ELEM_VALUE;
     }
   }
}

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
                   (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}

int main(int argc, char *argv[]) {

  const size_t n=1<<11;

  float **C0=allocate_matrix(n,n);
  float **C1=allocate_matrix(n,n);
  float **C2=allocate_matrix(n,n);
  float **A=allocate_matrix(n,n);
  float **B=allocate_matrix(n,n);

  srand(10);

  randomly_fill_matrix(A, n, n);
  randomly_fill_matrix(B, n, n);

  struct timespec b_time, e_time;

  for (size_t i=1; i<=n; i*=2) {
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
    float * C_tmp = strassen_opt(A, B, i);
    clock_gettime(CLOCK_REALTIME, &e_time);

    printf("\t%lf", get_execution_time(b_time, e_time));

    int count = 0;
    for(size_t j = 0; j < i; ++j)
    {

      C2[j] = &C_tmp[count];
      count += i;
    }
    printf("\t%d\n", same_matrix(C0, i, i, C1, i, i));
    printf("\t%d\n", same_matrix(C0, i, i, C2, i, i));
  }


  deallocate_matrix(C0,n);
  deallocate_matrix(C1,n);
  deallocate_matrix(C2,n);
  deallocate_matrix(A,n);
  deallocate_matrix(B,n);

  return 0;
}
