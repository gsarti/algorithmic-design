#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "chain_mm.h"
#include "../utility.h"


#define REPETITIONS 3
#define BILLION 1E9


size_t *build_dimensions(const size_t n) {
  size_t *dims = (size_t *)malloc(sizeof(size_t) * (n + 1));

  for (size_t i = 0; i < n + 1; i++) {
    dims[i] = rand() % 600;
  }

  return dims;
}

float ***build_problem_instance(const size_t *dims, const size_t n) {
  float ***A = (float ***)malloc(sizeof(float **) * n);

  for (size_t i = 0; i < n; i++) {
    A[i] = allocate_matrix(dims[i], dims[i + 1]);
  }

  return A;
}

int main() {
  size_t n = 30;

  size_t *dims = build_dimensions(n);
  float ***As = build_problem_instance(dims, n);

  struct timespec requestStart, requestEnd;
  double accum;

  printf("Input Size\tOptimal Solution\tNaive Solution\n");
  for (size_t d = 1; d < n; d++) {
    printf("%ld", d);
    clock_gettime(CLOCK_REALTIME, &requestStart);
    for (int r = 0; r < REPETITIONS; r++) {
      size_t **S = ChainMatrixMul(dims, d);

      float **R = evaluate_CMM(As, dims, d, S);

      deallocate_matrix((void **)R, dims[0]);
      deallocate_matrix((void **)S, d);
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    accum = (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;

    printf("\t\t%lf", (accum / REPETITIONS));
    clock_gettime(CLOCK_REALTIME, &requestStart);
    for (int r = 0; r < REPETITIONS; r++) {

      float **R = evaluate_naive_CMM(As, dims, d);
      deallocate_matrix((void **)R, dims[0]);
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    accum = (requestEnd.tv_sec - requestStart.tv_sec) +
            (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION;

    printf("\t\t%lf\n", (accum / REPETITIONS));
  }

  for (size_t i = 0; i < n; i++) {
    deallocate_matrix((void **)As[i], dims[i]);
  }
  free(As);
  free(dims);
}
