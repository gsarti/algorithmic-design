#ifndef __CHAIN_MATRIX_MULTIPLICATION__

#include <stdlib.h>

size_t **ChainMatrixMul(size_t *dim, size_t n);
float **evaluate_CMM(float ***As, size_t *dims, const size_t n, size_t **S);
float **evaluate_naive_CMM(float ***As, size_t *dims, const size_t n);
void print_out_parenthesis(size_t **S, size_t n);

#endif // __CHAIN_MATRIX_MULTIPLICATION__
