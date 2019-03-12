#include <stdlib.h>

#include "matrix.h"

void sum_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n)
{
  // for all the rows in the blocks
  for (size_t i=0; i<n; i++) {

    // for all the cols in the blocks
    for (size_t j=0; j<n; j++) {
      C[C_f_row+i][C_f_col+j] = A[A_f_row+i][A_f_col+j] +
                                B[B_f_row+i][B_f_col+j];
    }
  }
}

void sub_matrix_blocks(float **C,
                       const size_t C_f_row,
                       const size_t C_f_col,
                       float ** A,
                       const size_t A_f_row,
                       const size_t A_f_col,
                       float ** B,
                       const size_t B_f_row,
                       const size_t B_f_col,
                       const size_t n)
{
  // for all the rows in the blocks
  for (size_t i=0; i<n; i++) {

    // for all the cols in the blocks
    for (size_t j=0; j<n; j++) {
      C[C_f_row+i][C_f_col+j] = A[A_f_row+i][A_f_col+j] -
                                B[B_f_row+i][B_f_col+j];
    }
  }
}

void naive_aux(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
   for (size_t i=0; i<n; i++) {
     for (size_t j=0; j<n; j++) {
       C[C_f_row+i][C_f_col+j] = 0.0;
       for (size_t k=0; k<n; k++) {
         C[C_f_row+i][C_f_col+j] += (A[A_f_row+i][A_f_col+k]*
                                     B[B_f_row+k][B_f_col+j]);
       }
     }

   }
}

void strassen_aux(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
  if (n < (1<<6)) {
    naive_aux(C, C_f_row, C_f_col,
              A, A_f_row, A_f_col,
              B, B_f_row, B_f_col,
              n);
    return;
  }

  const size_t n2=n/2;

  const size_t C1X = C_f_row;
  const size_t C2X = C_f_row + n2;
  const size_t CX1 = C_f_col;
  const size_t CX2 = C_f_col + n2;

  const size_t A1X = A_f_row;
  const size_t A2X = A_f_row + n2;
  const size_t AX1 = A_f_col;
  const size_t AX2 = A_f_col + n2;

  const size_t B1X = B_f_row;
  const size_t B2X = B_f_row + n2;
  const size_t BX1 = B_f_col;
  const size_t BX2 = B_f_col + n2;

  float ***S=(float ***)malloc(sizeof(float **)*10);
  for (int i=0; i<10; i++) {
    S[i] = allocate_matrix(n2, n2);
  }

  float ***P=(float ***)malloc(sizeof(float **)*7);
  for (int i=0; i<7; i++) {
    P[i] = allocate_matrix(n2, n2);
  }

  // S1 = B12 - B22
  sub_matrix_blocks(S[0],0,0,
                    B,B1X,BX2,
                    B,B2X,BX2,
                    n2);

  // S2 = A11 + A12
  sum_matrix_blocks(S[1],0,0,
                    A,A1X,AX1,
                    A,A1X,AX2,
                    n2);

  // S3 = A21 + A22
  sum_matrix_blocks(S[2],0,0,
                    A,A2X,AX1,
                    A,A2X,AX2,
                    n2);

  // S4 = B21 - B11
  sub_matrix_blocks(S[3],0,0,
                    B,B2X,BX1,
                    B,B1X,BX1,
                    n2);

  // S5 = A11 + A22
  sum_matrix_blocks(S[4],0,0,
                    A,A1X,AX1,
                    A,A2X,AX2,
                    n2);

  // S6 = B11 + B22
  sum_matrix_blocks(S[5],0,0,
                    B,B1X,BX1,
                    B,B2X,BX2,
                    n2);

  // S7 = A12 - A22 (there was a bug here A21 - A22)
  sub_matrix_blocks(S[6],0,0,
                    A,A1X,AX2,
                    A,A2X,AX2,
                    n2);
  // S8 = B21 + B22 (there was a bug here B21 - B22)
  sum_matrix_blocks(S[7],0,0,
                    B,B2X,BX1,
                    B,B2X,BX2,
                    n2);

  // S9 = A11 - A21
  sub_matrix_blocks(S[8],0,0,
                    A,A1X,AX1,
                    A,A2X,AX1,
                    n2);

  // S10 = B11 + B12
  sum_matrix_blocks(S[9],0,0,
                    B,B1X,BX1,
                    B,B1X,BX2,
                    n2);

  // P1 = A11 x S1
  strassen_aux(P[0], 0, 0,
               A, A1X, AX1,
               S[0], 0, 0,
               n2);

  // P2 = S2 x B22
  strassen_aux(P[1], 0, 0,
               S[1], 0, 0,
               B, B2X, BX2,
               n2);

  // P3 = S3 x B11
  strassen_aux(P[2], 0, 0,
               S[2], 0, 0,
               B, B1X, BX1,
               n2);

  // P4 = A22 x S4
  strassen_aux(P[3], 0, 0,
               A, A2X, AX2,
               S[3], 0, 0,
               n2);

  // P5 = S5 x S6
  strassen_aux(P[4], 0, 0,
               S[4], 0, 0,
               S[5], 0, 0,
               n2);

  // P6 = S7 x S8
  strassen_aux(P[5], 0, 0,
               S[6], 0, 0,
               S[7], 0, 0,
               n2);

  // P7 = S9 x S10
  strassen_aux(P[6], 0, 0,
               S[8], 0, 0,
               S[9], 0, 0,
               n2);

  // C11 = (P5 + P4) - P2 + P6
  sum_matrix_blocks(C, C1X, CX1,
                    P[4], 0, 0,
                    P[3], 0, 0,
                    n2);

  sub_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    P[1], 0, 0,
                    n2);

  sum_matrix_blocks(C, C1X, CX1,
                    C, C1X, CX1,
                    P[5], 0, 0,
                    n2);

  // C12 = P1 + P2
  sum_matrix_blocks(C, C1X, CX2,
                    P[0], 0, 0,
                    P[1], 0, 0,
                    n2);

  // C21 = P3 + P4
  sum_matrix_blocks(C, C2X, CX1,
                    P[2], 0, 0,
                    P[3], 0, 0,
                    n2);

  // C22 = P5 + P1 - P3 - P7
  sum_matrix_blocks(C, C2X, CX2,
                    P[4], 0, 0,
                    P[0], 0, 0,
                    n2);

  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    P[2], 0, 0,
                    n2);

  sub_matrix_blocks(C, C2X, CX2,
                    C, C2X, CX2,
                    P[6], 0, 0,
                    n2);

  for (int i=0; i<10; i++) {
    deallocate_matrix(S[i], n2);
  }

  for (int i=0; i<7; i++) {
    deallocate_matrix(P[i], n2);
  }
}

void strassen(float **C,
      float **A, float **B, const size_t n)
{
  strassen_aux(C, 0, 0, A, 0, 0, B, 0, 0, n);
}
