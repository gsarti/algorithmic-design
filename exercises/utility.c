/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Utility methods for the assignments - Source
 * @date 29-06-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utility.h"

void swap(float* a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

void swap_int(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int leq(int a, int b)
{
    return a <= b;
}

int geq(int a, int b)
{
    return a >= b;
}

void naive_matrix_mult(float **C, float **A, float **B,
                       const size_t A_rows, const size_t A_cols,
                       const size_t B_rows, const size_t B_cols)
{
    if (A_cols != B_rows) {
       return;
    }

    for (size_t i=0; i<A_rows; i++) 
    {
        for (size_t j=0; j<B_cols; j++) 
        {
            C[i][j] = 0.0;
            for (size_t k=0; k<A_cols; k++) 
            {
                C[i][j] += (A[i][k]*B[k][j]);
            }
        }
    }
}

float **allocate_matrix(const size_t rows, const size_t cols)
{
    float **A=(float **)malloc(sizeof(float *)*rows);

    for (size_t i=0; i<rows; i++) 
    {
        A[i]=(float *)malloc(sizeof(float)*cols);
    }
    return A;
}

int **allocate_matrix_int(const size_t rows, const size_t cols)
{
    int **A=(int **)malloc(sizeof(int *)*rows);

    for (size_t i=0; i<rows; i++) 
    {
        A[i]=(int *)malloc(sizeof(int)*cols);
    }
    return A;
}

unsigned int **allocate_matrix_unsigned_int(const size_t rows, const size_t cols)
{
    unsigned int **A=(unsigned int **)malloc(sizeof(unsigned int *)*rows);

    for (size_t i=0; i<rows; i++) 
    {
        A[i]=(unsigned int *)malloc(sizeof(unsigned int)*cols);
    }
    return A;
}

void deallocate_matrix(void **A, const size_t rows)
{
  for (size_t i = 0; i < rows; i++) 
  {
    free(A[i]);
  }
  free(A);
}

float **copy_matrix(float **A, const size_t rows, const size_t cols)
{
    float **C = allocate_matrix(rows, cols);
    for (size_t i=0; i<rows; i++) 
    {
        for (size_t j=0; j<cols; j++) 
        {
            C[i][j]=A[i][j];
        }
    }
    return C;
}

int **copy_matrix_int(int **A, const size_t rows, const size_t cols)
{
    int **C = allocate_matrix_int(rows, cols);
    for (size_t i=0; i<rows; i++) 
    {
        for (size_t j=0; j<cols; j++) 
        {
            C[i][j]=A[i][j];
        }
    }
    return C;
}

void copy_array_int(int *a, int *b, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        a[i] = b[i];
    }
}

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		        float **B, const size_t B_rows, const size_t B_cols)
{
    if ((A_rows != B_rows) || (A_cols != B_cols)) 
    {
        return 0;
    }
    for (size_t i=0; i<A_rows; i++) 
    {
        for (size_t j=0; j<A_cols; j++) 
        {
            if (A[i][j] != B[i][j]) 
            {
	            return 0;
            }
        }
    }
    return 1;
}

int same_matrix_int(int **A, const size_t A_rows, const size_t A_cols,
		            int **B, const size_t B_rows, const size_t B_cols)
{
    if ((A_rows != B_rows) || (A_cols != B_cols)) 
    {
        return 0;
    }
    for (size_t i=0; i<A_rows; i++) 
    {
        for (size_t j=0; j<A_cols; j++) 
        {
            if (A[i][j] != B[i][j]) 
            {
	            return 0;
            }
        }
    }
    return 1;
}

int same_matrix_approx(float **A, const size_t A_rows, const size_t A_cols,
		               float **B, const size_t B_rows, const size_t B_cols,
                       float prec)
{
    if ((A_rows != B_rows) || (A_cols != B_cols)) 
    {
        return 0;
    }
    for (size_t i=0; i<A_rows; i++) 
    {
        for (size_t j=0; j<A_cols; j++) 
        {
            float ratio = A[i][j] / B[i][j];
            float err = 1 - ratio > 0 ? 1 - ratio : ratio - 1;
            if (err > prec)
                return 0;
        }
    }
    return 1;
}

void randomly_fill_matrix(float **A, const size_t rows, 
                          const size_t cols, const int max)
{
    for (size_t i=0; i< rows; i++) 
    {
        for (size_t j=0; j< cols; j++) 
        {
   	        A[i][j]=rand() % (2 * max) - max;
        }
    }
}

void randomly_fill_matrix_int(int **A, const size_t rows, 
                              const size_t cols, const int max)
{
    for (size_t i=0; i< rows; i++) 
    {
        for (size_t j=0; j< cols; j++) 
        {
   	        A[i][j]=(int)(rand() % (2 * max) - max);
        }
    }
}

void randomly_fill_matrix_unsigned_int(unsigned int **A, const size_t rows, 
                                       const size_t cols, const unsigned int max)
{
    for (size_t i=0; i< rows; i++) 
    {
        for (size_t j=0; j< cols; j++) 
        {
   	        A[i][j]=(unsigned int)(rand() % max);
        }
    }
}

void randomly_fill_matrix_unif(float **A, const size_t rows, const size_t cols)
{
    for (size_t i=0; i< rows; i++) 
    {
        for (size_t j=0; j< cols; j++) 
        {
   	        A[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
}

void print_matrix(float **A, const size_t rows, const size_t cols)
{
    printf("\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%f, ", A[i][j]);
        }
        printf("\n");
    }
}

void print_array(float *a, const size_t n)
{
    printf("\n");
    for(int i = 0; i < n; i++)
    {
        printf("%f, ", a[i]);
    }
}

void print_matrix_int(int **A, const size_t rows, const size_t cols)
{
    printf("\n");
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            printf("%d, ", A[i][j]);
        }
        printf("\n");
    }
}

void print_array_int(int *a, const size_t n)
{
    printf("\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d, ", a[i]);
    }
}

int max_array_int(int* array, size_t size)
{
    int max = array[0];
    for (size_t i = 0; i < size; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
         (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}