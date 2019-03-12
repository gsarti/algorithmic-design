#include <stdlib.h>

int naive_matrix_mult(float **C,
                        float **A,
                        float **B,
                        const size_t A_rows,
                        const size_t A_cols,
                        const size_t B_rows,
                        const size_t B_cols)
{
  if (A_cols != B_rows) {
     return -1;
  }

  // for all rows in A
  for (size_t i=0; i<A_rows; i++) {

     // for all cols in B
     for (size_t j=0; j<B_cols; j++) {

       // reset C[i][j]
       C[i][j] = 0.0;

       // sum all the element mults
       for (size_t k=0; k<A_cols; k++) {
        C[i][j] += (A[i][k]*B[k][j]);
       }
     }
  }

  return 0;
}

float **allocate_matrix(const size_t rows,
                        const size_t cols)
{
   float **A=(float **)malloc(sizeof(float *)*rows);

   for (size_t i=0; i<rows; i++) {
     A[i]=(float *)malloc(sizeof(float)*cols);
   }

   return A;
}

void deallocate_matrix(float **A, const size_t rows)
{
  for (size_t i=0; i<rows; i++) {
    free(A[i]);
  }

  free(A);
}

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		float **B, const size_t B_rows, const size_t B_cols)
{
   if ((A_rows != B_rows) || (A_cols != B_cols)) {
     return 0;
   }

   for (size_t i=0; i<A_rows; i++) {
     for (size_t j=0; j<A_cols; j++) {
        if (A[i][j] != B[i][j]) {
	         return 0;
        }
     }
   }

   return 1;
}
