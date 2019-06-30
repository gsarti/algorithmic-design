/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Utility methods for the assignments - Headers
 * @date 29-06-2019
 */

#ifndef UTILITY_H__
#define UTILITY_H__

#include <stdlib.h>

/**
 * @brief Swaps the content of two integer pointers
 * @param  a  The first integer pointer
 * @param  b  The second integer pointer
 */
void swap(int * a, int * b);

/**
 * @brief Performs a naive matrix multiplication
 * @param  C               Result matrix.
 * @param  A, B            Matrices to be multiplied together.
 * @param  A_rows, A_cols  Dimensions of the A matrix.
 * @param  B_rows, B_cols  Dimensions of the B matrix. 
 */
void naive_matrix_mult(float **C, float **A, float **B,
                      const size_t A_rows, const size_t A_cols,
                      const size_t B_rows, const size_t B_cols);

/**
 * @brief Copies a matrix of floats.
 * @param    A           The matrix to be copied.
 * @param    rows, cols  The dimensions of the A matrix.
 * @return   float       The copied matrix.
 */
float **copy_matrix(float **A, const size_t rows, const size_t cols);

/**
 * @brief Allocates a matrix of size rows, cols in memory
 * @param    rows, cols  The dimensions of the matrix.
 * @return   float       The allocated matrix.
 */
float **allocate_matrix(const size_t rows, const size_t cols);

/**
 * @brief Deallocates a matrix from memory.
 * @param    rows  The rows of the matrix.
 */
void deallocate_matrix(void **A, const size_t rows);

// Returns 1 if A and B are equal, 0 otherwise.
int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		        float **B, const size_t B_rows, const size_t B_cols);

/**
 * @brief Randomly fills matrix A with values between 0 and max.
 */
void randomly_fill_matrix(float **A, const size_t A_rows, 
                          const size_t A_cols, int max);

/**
 * @brief Get the execution time in seconds.
 * @param    b_time  Beginning time object.
 * @param    e_time  End time object.
 * @return double Time in seconds.
 */
double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time);

#endif //UTILITY_H__