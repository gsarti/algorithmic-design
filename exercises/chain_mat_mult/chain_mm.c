#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"

#define CMM(M, row, col) M[row][col - row]


/**
  Solve the Chain Matrix Multiplication Problem

  Takes the array of dimentions of the matrixes

  Returns the matrix S
*/
size_t **ChainMatrixMul(size_t *dim, size_t n) {
  /* INITIALIZATION */
  size_t **M = (size_t **)malloc(sizeof(size_t *) * n);
  size_t **S = (size_t **)malloc(sizeof(size_t *) * n);

  for (size_t i = 0; i < n; i++) {
    M[i] = (size_t *)malloc(sizeof(size_t) * (n - i));
    S[i] = (size_t *)malloc(sizeof(size_t) * (n - i));

    CMM(M, i, i) = 0;
    CMM(S, i, i) = i;
  }
  /* END INITIALIZATION */

  for (size_t l = 1; l < n; l++) {       /* for all the diag up to
                                            the rightmost one */
    for (size_t i = 0; i < n - l; i++) { /* BUG1: i was in [0,l) */
      size_t j = l + i;                  /* BUG2: j was l-i */

      /* Searching for the best split between i and j */
      CMM(M, i, j) =
          CMM(M, i, j - 1) + CMM(M, j, j) + (dim[i] * dim[j + 1]) * dim[j];
      CMM(S, i, j) = j - 1;

      // printf("Searching %ld %ld\n", i, j);
      for (size_t k = i + 1; k < j; k++) {
        // printf("%ld %ld %ld\n", i, k+1, j);
        size_t c = CMM(M, i, k) + CMM(M, k + 1, j) +
                   (dim[i] * dim[j + 1]) * dim[k + 1];

        if (c < CMM(M, i, j)) {
          CMM(M, i, j) = c;
          CMM(S, i, j) = k;
        }
      }
    }
  }

  for (size_t i = 0; i < n; i++) {
    free(M[i]);
  }

  free(M);

  return S;
}

float **evaluate_CMM_aux(float ***As, size_t *dims, const size_t n, size_t **S,
                         size_t i, size_t j) {

  if (i == j) {
    return copy_matrix(As[i], dims[i], dims[j + 1]);
  }

  size_t p = CMM(S, i, j);

  float **C1 = evaluate_CMM_aux(As, dims, n, S, i, p);
  float **C2 = evaluate_CMM_aux(As, dims, n, S, p + 1, j);

  float **R = allocate_matrix(dims[i], dims[j + 1]);

  naive_matrix_mult(R, C1, C2, dims[i], dims[p + 1], dims[p + 1], dims[j + 1]);

  deallocate_matrix((void **)C1, dims[i]);
  deallocate_matrix((void **)C2, dims[p + 1]);
  return R;
}

float **evaluate_CMM(float ***As, size_t *dims, const size_t n, size_t **S) {
  return evaluate_CMM_aux(As, dims, n, S, 0, n - 1);
}

float **evaluate_naive_CMM(float ***As, size_t *dims, const size_t n) {
  float **C = copy_matrix(As[0], dims[0], dims[1]);
  float **R;

  for (size_t i = 1; i < n; i++) {
    R = allocate_matrix(dims[0], dims[i + 1]);

    naive_matrix_mult(R, C, As[i], dims[0], dims[i], dims[i], dims[i + 1]);

    deallocate_matrix((void **)C, dims[0]);
    C = R;
  }

  return C;
}

void print_out_parenthesis_aux(size_t **S, size_t i, size_t j) {
  if (i == j) {
    return;
  }

  printf("%ld\t", CMM(S, i, j));
  print_out_parenthesis_aux(S, i, CMM(S, i, j));
  print_out_parenthesis_aux(S, CMM(S, i, j) + 1, j);
}

void print_out_parenthesis(size_t **S, size_t n) {
  print_out_parenthesis_aux(S, 0, n - 1);
}
