/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Optimized Strassen implementation - Header
 * @date 30-06-2019
 */

#ifndef __HOMEWORK__

#include <stdlib.h>

/**
 * @brief A matrix of float values.
 * @var mat  A pointer to pointers of float for matrix values.
 * @var row  Row dimension of mat.
 * @var col  Col dimensions of mat.
 */
typedef struct Matrix 
{
    float ** mat;
    const size_t row;
    const size_t col;
} Matrix;

// Sums two matrix blocks A, B of size "size" creating block C.
void sum_blocks(Matrix A, Matrix B, Matrix C, const size_t size);

// Subtracts two matrix blocks A, B of size "size" creating block C.
void sub_blocks(Matrix A, Matrix B, Matrix C, const size_t size);

// Naive matrix multiplication of A, B of size "size" creating C.
void naive_mult(Matrix A, Matrix B, Matrix C, const size_t size);

// Auxiliary method for the optimized implementation of Strassen's algorithm.
void strassen_aux_opt(Matrix A, Matrix B, Matrix C, Matrix M, const size_t size);

/**
 * @brief Performs the matrix multiplication of squared matrices A, B
 *        of size n x n using the optimized Strassen algorithm.
 * @param  C     The resulting matrix.
 * @param  A, B  The squared matrices that should be multiplied.
 * @param  n     The size of a side of matrices A, B
 * 
 * The number of allocations is minimized by reusing temporarily blocks
 * of the resulting matrix C and performing allocation outside of the 
 * auxiliary function call.
 */
void strassen_opt(float **C, float **A, float **B, const size_t n);

#endif // __HOMEWORK__