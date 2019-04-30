#ifndef __MATRIX__

#include <stdlib.h>

int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols);

float **copy_matrix(float **A, const size_t rows,
                        const size_t cols);

float **allocate_matrix(const size_t rows,
                        const size_t cols);

void deallocate_matrix(void **A, const size_t rows);

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols);

#endif // __MATRIX__
