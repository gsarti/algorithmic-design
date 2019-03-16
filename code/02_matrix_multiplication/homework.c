#include <stdlib.h>

#include "matrix.h"

typedef struct Matrix 
{
    float ** mat;
    const size_t row;
    const size_t col;
} Matrix;

void sum_blocks(Matrix A, Matrix B, Matrix C, const size_t size)
{
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      C.mat[C.row + i][C.col + j] = A.mat[A.row + i][A.col + j] +
                                    B.mat[B.row + i][B.col + j];
    }
  }
}

void sub_blocks(Matrix A, Matrix B, Matrix C, const size_t size)
{
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      C.mat[C.row + i][C.col + j] = A.mat[A.row + i][A.col + j] -
                                    B.mat[B.row + i][B.col + j];
    }
  }
}

void naive_mult(Matrix A, Matrix B, Matrix C, const size_t size)
{
   for (size_t i = 0; i < size; i++) {
     for (size_t j = 0; j < size; j++) {
       C.mat[C.row + i][C.col + j] = 0.0;
       for (size_t k=0; k<size; k++) {
         C.mat[C.row + i][C.col + j] += (A.mat[A.row + i][A.col + k] *
                                         B.mat[B.row + k][B.col + j]);
       }
     }
   }
}

void strassen_aux_opt(Matrix A, Matrix B, Matrix C, Matrix M, const size_t size)
{
  if (size < (1 << 6)) {
    naive_mult(A, B, C, size);
    return;
  }

  const size_t half_size = size / 2;

  Matrix A11 = {A.mat, A.row,             A.col};
  Matrix A12 = {A.mat, A.row,             A.col + half_size};
  Matrix A21 = {A.mat, A.row + half_size, A.col};
  Matrix A22 = {A.mat, A.row + half_size, A.col + half_size};
  Matrix B11 = {B.mat, B.row,             B.col};
  Matrix B12 = {B.mat, B.row,             B.col + half_size};
  Matrix B21 = {B.mat, B.row + half_size, B.col};
  Matrix B22 = {B.mat, B.row + half_size, B.col + half_size};
  Matrix C11 = {C.mat, C.row,             C.col};
  Matrix C12 = {C.mat, C.row,             C.col + half_size};
  Matrix C21 = {C.mat, C.row + half_size, C.col};
  Matrix C22 = {C.mat, C.row + half_size, C.col + half_size};
  Matrix M11 = {M.mat, M.row,             M.col};
  Matrix M12 = {M.mat, M.row,             M.col + half_size};
  Matrix M21 = {M.mat, M.row + half_size, M.col};
  Matrix M22 = {M.mat, M.row + half_size, M.col + half_size};

  // S2 = A11 + A12
  sum_blocks(A11, A12, C12, half_size);
  // P2 = S2 x B22
  strassen_aux_opt(C12, B22, C12, M22, half_size);

  // S4 = B21 - B11
  sub_blocks(B21, B11, C21, half_size);
  // P4 = A22 x S4
  strassen_aux_opt(A22, C21, C21, M22, half_size);

  // S5 = A11 + A22
  sum_blocks(A11, A22, C22, half_size);
  // S6 = B11 + B22
  sum_blocks(B11, B12, M11, half_size);
  // P5 = S5 x S6
  strassen_aux_opt(C22, M11, C22, M22, half_size);

  // S7 = A12 - A22
  sub_blocks(A12, A22, C11, half_size);
  // S8 = B21 + B22
  sum_blocks(B21, B22, M11, half_size);
  // P6 = S7 x S8
  strassen_aux_opt(C11, M11, M11, M22, half_size);

  // C11 = (P5 + P4) - P2 + P6
  sum_blocks(C22, C21, C11, half_size);
  sum_blocks(C12, M11, M11, half_size);
  sub_blocks(C11, M11, C11, half_size);

  // S1 = B12 - B22
  sub_blocks(B12, B22, M11, half_size);
  // P1 = A11 x S1
  strassen_aux_opt(A11, M11, M11, M22, half_size);

  // C12 = P1 + P2
  sum_blocks(M11, C12, C12, half_size);

  // S3 = A21 + A22
  sum_blocks(A21, A22, M12, half_size);
  // P3 = S3 x B11
  strassen_aux_opt(M12, B11, M12, M22, half_size);

  // C21 = P3 + P4
  sum_blocks(M12, C21, C21, half_size);

  // Partial = P5 + P1 - P3
  sum_blocks(C22, M11, C22, half_size);
  sub_blocks(C22, M12, C22, half_size);

  // S9 = A11 - A21
  sub_blocks(A11, A21, M11, half_size);
  // S10 = B11 + B12
  sum_blocks(B11, B12, M12, half_size);
  // P7 = S9 x S10 (replaces P2 in tmp_prod2)
  strassen_aux_opt(M11, M12, M11, M22, half_size);

  // C22 = Partial - P7
  sub_blocks(C22, M11, C22, half_size);
}

void strassen_opt(float **C, float **A, float **B, const size_t size)
{
  Matrix M_A = {A, 0, 0};
  Matrix M_B = {B, 0, 0};
  Matrix M_C = {C, 0, 0};
  Matrix aux = {allocate_matrix(size, size), 0, 0};
  strassen_aux_opt(M_A, M_B, M_C, aux, size);
  deallocate_matrix(aux.mat, size);
}
