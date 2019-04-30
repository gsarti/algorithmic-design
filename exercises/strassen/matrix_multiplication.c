#include <stdlib.h>

void naive_matrix_mult(float **C, 
                       float **A, 
                       float** B,
                       const size_t A_rows,
                       const size_t A_cols,
                       const size_t B_rows,
                       const size_t B_cols)
{
    if (A_cols != B_rows)
        return -1;
    for (size_t i = 0; i < A_rows; i++)
    {
        for (size_t j = 0; j < B_cols; j++)
        {
            C[i][j] = 0.0;
            for (size_t k = 0; k < A_cols; k++)
            {
                C[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }
    return 0;
}

/**
 * For using the Strassen's algorithm, we define a block through
 * the matrix that contains it, its top-leftmost element and the
 * size of the block.
 */

void sum_matrix_blocks(float **C,
                       const size_t C_first_row,
                       const size_t C_first_col,
                       float **A,
                       const size_t A_first_row,
                       const size_t A_first_col,
                       float **B,
                       const size_t B_first_row,
                       const size_t B_first_col,
                       const size_t block_size)
{
    //For all rows in the block
    for (size_t i = 0; i < block_size; i++)
    {
        //For all columns in the block
        for(size_t j = 0; j < block_size; j++)
        {
            //Sum element-wise elements in the blocks
            C[C_first_row + i][C_first_col + j] = A[A_first_row + i][A_first_col + j] +
                                                  B[B_first_row + i][A_first_col + j];
        }
    }
}

void subtract_matrix_blocks(float **C,
                       const size_t C_first_row,
                       const size_t C_first_col,
                       float **A,
                       const size_t A_first_row,
                       const size_t A_first_col,
                       float **B,
                       const size_t B_first_row,
                       const size_t B_first_col,
                       const size_t block_size)
{
    //For all rows in the block
    for (size_t i = 0; i < block_size; i++)
    {
        //For all columns in the block
        for(size_t j = 0; j < block_size; j++)
        {
            //Subtract element-wise in the block
            C[C_first_row + i][C_first_col + j] = A[A_first_row + i][A_first_col + j] -
                                                  B[B_first_row + i][A_first_col + j];
        }
    }
}

/**
 * @brief Reimplementation of the naive matrix multiplication
 * algorithm using blocks.
 */
void naive_block_matrix_mult(float **C,
                             const size_t C_first_row,
                             const size_t C_first_col,
                             float **A,
                             const size_t A_first_row,
                             const size_t A_first_col,
                             float **B,
                             const size_t B_first_row,
                             const size_t B_first_col,
                             const size_t block_size)
{
    for (size_t i = 0; i < block_size; i++)
    {
        for (size_t j = 0; j < block_size; j++)
        {
            C[C_first_row + i][C_first_col + j] = 0.0;
            for (size_t k = 0; k < block_size; k++)
            {
                C[C_first_row + i][C_first_col + j] += A[A_first_row + i][A_first_col + k] *
                                                       B[B_first_row + k][A_first_col + j];
            }
        }
    }
    return 0;
}

float **allocate_matrix(const size_t rows,
                        const size_t cols)
{
    float **A = (float **)malloc(sizeof(float)* rows);

    for(size_t i = 0; i < rows; i++)
    {
        A[i] = (float *)malloc(sizeof(float) * cols);
    }
    return A;
}

void deallocate_matrix(float **A, const size_t rows)
{
    for(size_t i = 0; i < rows; i++)
    {
        free(A[i]);
    }
    free(A);
}

void strassen_auxiliary(float **C,
                        const size_t C_first_row,
                        const size_t C_first_col,
                        float **A,
                        const size_t A_first_row,
                        const size_t A_first_col,
                        float **B,
                        const size_t B_first_row,
                        const size_t B_first_col,
                        const size_t size)
{
    // Base case
    if (size < 2)
    {
        naive_block_matrix_mult(C, C_first_row, C_first_col,
                                A, A_first_row, A_first_col,
                                B, B_first_row, B_first_col, size);
    }

    const size_t half_size = size / 2;

    //Coordinates of the top element of the top element for the
    //four blocks of the three matrices

    const size_t C1X = C_first_row;
    const size_t C2X = C_first_row + half_size;
    const size_t CX1 = C_first_row;
    const size_t CX2 = C_first_row;

    const size_t B1X = B_first_row;
    const size_t B2X = B_first_row + half_size;
    const size_t BX1 = B_first_row;
    const size_t BX2 = B_first_row;

    const size_t A1X = A_first_row;
    const size_t A2X = A_first_row + half_size;
    const size_t AX1 = A_first_row;
    const size_t AX2 = A_first_row;

    float ***S = (float ***)malloc(sizeof(float ***) * 10);
    for (int i = 0; i < 10; i++)
    {
        S[i] = allocate_matrix(half_size, half_size);
    }

    float ***P = (float ***)malloc(sizeof(float ***) * 7);
    for (int i = 0; i < 7; i++)
    {
        P[i] = allocate_matrix(half_size, half_size);
    }

    //Building the sums and the products

    //S1 = B12 - B22
    subtract_matrix_blocks(S[0], 0, 0,
                           B, B1X, BX2,
                           B, B2X, BX2, half_size);
    //S2 = A11 + A12
    sum_matrix_blocks(S[1], 0, 0,
                      A, A1X, AX1,
                      A, A1X, AX2, half_size);

    //S3 = A21 + A22
    sum_matrix_blocks(S[2], 0, 0,
                      A, A2X, AX1,
                      A, A2X, AX2, half_size);

    //S4 = B21 - B11
    subtract_matrix_blocks(S[3], 0, 0,
                           B, B2X, BX1,
                           B, B1X, BX1, half_size);

    //S5 = A11 + A22
    sum_matrix_blocks(S[4], 0, 0,
                      A, A1X, AX1,
                      A, A2X, AX2, half_size); 

    //S6 = B11 + B22
    sum_matrix_blocks(S[5], 0, 0,
                    B, B1X, BX1,
                    B, B2X, BX2, half_size);

    //S7 = A12 - A22
    subtract_matrix_blocks(S[6], 0, 0,
                      A, A1X, AX2,
                      A, A2X, AX2, half_size);

    //S8 = B21 + B22
    sum_matrix_blocks(S[7], 0, 0,
                           B, B2X, BX1,
                           B, B2X, BX2, half_size);

    //S9 = A11 - A21
    subtract_matrix_blocks(S[8], 0, 0,
                      A, A1X, AX1,
                      A, A2X, AX1, half_size);

    //S10 = B11 + B12
    sum_matrix_blocks(S[9], 0, 0,
                      B, B1X, BX1,
                      B, B1X, BX2, half_size);

    //P1 = A11 x S1
    strassen_auxiliary(P[0], 0, 0,
                       A, A1X, AX1,
                       S[0], 0, 0, half_size);

    //P2 = S2 x B22
    strassen_auxiliary(P[1], 0, 0,
                       S[1], 0, 0,
                       B, B2X, BX2, half_size);

    //P3 = S3 x B11
    strassen_auxiliary(P[2], 0, 0,
                       S[2], 0, 0,
                       B, B1X, BX1, half_size);
    
    //P4 = A22 x S4
    strassen_auxiliary(P[3], 0, 0,
                       A, A2X, AX2,
                       S[3], 0, 0, half_size);

    //P5 = S5 x S6
    strassen_auxiliary(P[4], 0, 0,
                    S[4], 0, 0,
                    S[5], 0, 0, half_size);

    //P6 = S7 x S8
    strassen_auxiliary(P[5], 0, 0,
                    S[6], 0, 0,
                    S[7], 0, 0, half_size);

    //P7 = S9 x S10
    strassen_auxiliary(P[6], 0, 0,
                    S[8], 0, 0,
                    S[9], 0, 0, half_size);

    //C11 = P5 + P4 - P2 + P6
    sum_matrix_blocks(C, C1X, CX1,
                      P[4], 0, 0,
                      P[3], 0, 0, half_size);

    subtract_matrix_blocks(C, C1X, CX1,
                      C, C1X, CX1,
                      P[1], 0, 0, half_size);

    sum_matrix_blocks(C, C1X, CX1,
                      C, C1X, CX1,
                      P[5], 0, 0, half_size);

    //C12 = P1 + P2
    sum_matrix_blocks(C, C1X, CX2,
                      P[0], 0, 0,
                      P[1], 0, 0, half_size);
    
    //C21 = P3 + P4
    sum_matrix_blocks(C, C2X, CX1,
                      P[2], 0, 0,
                      P[3], 0, 0, half_size);

    //C22 = P5 + P1 - P3 - P7
    sum_matrix_blocks(C, C2X, CX2,
                      P[4], 0, 0,
                      P[0], 0, 0, half_size);

    subtract_matrix_blocks(C, C2X, CX2,
                      C, C2X, CX2,
                      P[2], 0, 0, half_size);

    subtract_matrix_blocks(C, C2X, CX2,
                      C, C2X, CX2,
                      P[6], 0, 0, half_size);
    

    for (int i = 0; i < 10; i++)
    {
        deallocate_matrix(S[i], half_size);
    }

    for (int i = 0; i < 7; i++)
    {
        deallocate_matrix(P[i], half_size);
    }
}

void strassen(float **C, 
              float**A,
              float**B,
              const size_t block_size)
{
    strassen_auxiliary(C,0,0,A,0,0,B,0,0,block_size);
}