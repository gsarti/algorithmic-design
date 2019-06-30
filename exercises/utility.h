/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Utility methods for the assignments - Headers
 * @date 29-06-2019
 */

#ifndef UTILITY_H__
#define UTILITY_H__

#include <stdlib.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/**
 * @brief Swaps the content of two pointers
 * @param  a  The first pointer
 * @param  b  The second pointer
 */
void swap(float* a, float *b);
void swap_int(int * a, int * b);

// Return 1 if a <= b (leq) or a >= b (geq), 0 otherwise.
int leq(int a, int b);
int geq(int a, int b);

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
 * @brief Allocates a matrix of size rows, cols in memory
 * @param    rows, cols  The dimensions of the matrix.
 * @return   float       The allocated matrix.
 */
float **allocate_matrix(const size_t rows, const size_t cols);
int **allocate_matrix_int(const size_t rows, const size_t cols);

/**
 * @brief Deallocates a matrix from memory.
 * @param    rows  The rows of the matrix.
 */
void deallocate_matrix(void **A, const size_t rows);

/**
 * @brief Copies a matrix.
 * @param    A           The matrix to be copied.
 * @param    rows, cols  The dimensions of the A matrix.
 * @return   float       The copied matrix.
 */
float **copy_matrix(float **A, const size_t rows, const size_t cols);
int **copy_matrix_int(int **A, const size_t rows, const size_t cols);
int *copy_vector_int(int *a, const size_t n);


// Returns 1 if A and B are equal, 0 otherwise.
int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		        float **B, const size_t B_rows, const size_t B_cols);
int same_matrix_int(int **A, const size_t A_rows, const size_t A_cols,
		            int **B, const size_t B_rows, const size_t B_cols);

// Returns 1 if A and B are approximately equal with precision prec, 0 otherwise
int same_matrix_approx(float **A, const size_t A_rows, const size_t A_cols,
		               float **B, const size_t B_rows, const size_t B_cols,
                       float prec);

// Randomly fills matrix A with values between 0 and max.
void randomly_fill_matrix(float **A, const size_t A_rows, 
                          const size_t A_cols, int max);
void randomly_fill_matrix_int(int **A, const size_t rows, 
                              const size_t cols, const int max);
void randomly_fill_matrix_unsigned_int(unsigned int **A, const size_t rows, 
                                       const size_t cols, const unsigned int max);

// Randomly fills matrix A with values sampled froma uniform distribution
void randomly_fill_matrix_unif(float **A, const size_t rows, const size_t cols);

// Prints the content of a matrix in console
void print_matrix(float **A, const size_t rows, const size_t cols);
void print_vector(float *a, const size_t n);
void print_matrix_int(int **A, const size_t rows, const size_t cols);
void print_vector_int(int *a, const size_t n);

/**
 * @brief Get the execution time in seconds.
 * @param    b_time  Beginning time object.
 * @param    e_time  End time object.
 * @return double Time in seconds.
 */
double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time);

#endif //UTILITY_H__