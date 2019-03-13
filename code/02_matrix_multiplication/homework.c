/**
 * @file homework.c
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Optimized implementation of the Strassen's algorithm
 * @date 2019-03-13
 * 
 * DISCLAIMER: As the cases shown in class, this implementation does not manage 
 * the cases in which matrices A and B aren't square matrices, or don't have a size
 * which is a multiple of 2. Specific padding functions should be implemented to manage
 * those cases, which are out of the scope of this course.
 * 
 * In the base case, we apply a optimized naive multiplication by transposing the B matrix
 * in order to make access by row faster for both matrices.
 * 
 * The output matrix C is expressed in terms of the block matrices M1..M7
 *
 * C1,1 = M1 + M4 - M5 + M7
 * C1,2 = M3 + M5
 * C2,1 = M2 + M4
 * C2,2 = M1 - M2 + M3 + M6
 * 
 * Each of the block matrices M1..M7 is composed of quadrants from A and B as follows:
 * 
 * M1 = AA[0] * BB[0] = (A1,1 + A2,2)(B1,1 + B2,2)
 * M2 = AA[1] * BB[1] = (A2,1 + A2,2)(B1,1)
 * M3 = AA[2] * BB[2] = (A1,1)(B1,2 - B2,2)
 * M4 = AA[3] * BB[3] = (A2,2)(B2,1 - B1,1)
 * M5 = AA[4] * BB[4] = (A1,1 + A1,2)(B2,2)
 * M6 = AA[5] * BB[5] = (A2,1 - A1,1)(B1,1 + B1,2)
 * M7 = AA[6] * BB[6] = (A1,2 - A2,2)(B2,1 + B2,2)
 * 
 * This approach has been shown to improve the performances w.r.t. the original Strassen implementation.
 * However, since it is n
*/

#include <stdlib.h>

float * naive_mult(const float * A, const float * b, size_t size)
{
  float t;
  size_t padding;
  /* Matrix transpose */
  float * row = NULL;
  float * B = (float *)malloc(sizeof(float) * size * size);
  float * C = (float *)malloc(sizeof(float) * size * size);
  const float * a_row = NULL;
  float * b_row = NULL;

  for(size_t i = 0; i < size; ++i)
  {
    row = &B[i * size];
    for(size_t j = 0; j < size; ++j)
    {
      row[j] = A[j * size + i];
    }
  }

  for(size_t i = 0; i < size; ++i)
  {
    padding = i * size;
    a_row = &A[padding];
    for(size_t j = 0; j < size; ++j)
    {
      t = 0.0;
      b_row = &B[j * size];
      for(size_t k = 0; k < size; ++k)
      {
        t += (a_row[k] * b_row[k]);
      }
      C[padding++] = t;
    }
  }

  free(B);
  return C;
}

/**
 * Assigns to the matrix C the sum of two quandrants of A using the given offsets
 */
void sum_inner_submatrices(float *C, const float * A,
                           size_t a_row_start, size_t a_col_start, 
                           size_t b_row_start, size_t b_col_start, 
                           size_t half, size_t size)
{
  size_t padding;
  size_t a_row_id;
  size_t b_row_id;
  const float *a_row;
  const float *b_row;

  for (size_t i = 0; i < half; i++)
  {
    padding = i * half;
    a_row_id = ((a_row_start + i) * size) + a_col_start;
    b_row_id = ((b_row_start + i) * size) + b_col_start;

    a_row = &A[a_row_id];
    b_row = &A[b_row_id];

    for (size_t j = 0; j < half; j++)
    {
      C[padding + j] = a_row[j] + b_row[j];
    }
  }
}

/**
 * Adds to the matrix C to the specified quadrant of A
 */
void sum_submatrix(float * C, const float * A, 
              size_t row_start, size_t col_start, 
              size_t half, size_t size)
{
  size_t padding;
  size_t row_id;
  float * row;

  for (size_t i = 0; i < half; i++)
  {
    padding = i * half;
    row_id = ((row_start + i) * size) + col_start;
    row = &C[row_id];

    for (size_t j = 0; j < half; j++)
    {
      row[j] += A[padding + j];
    }
  }
}

/**
 * Assigns to specified quadrant of C the sum of A and B
 */
void sum_outer_submatrices(float * C, const float * A, const float * B, 
            size_t row_start, size_t col_start, 
            size_t half, size_t size)
{
  size_t padding;
  size_t row_id;
  float * row;

  for (size_t i = 0; i < half; i++)
  {
    padding = i * half;
    row_id = ((row_start + i) * size) + col_start;
    row = &C[row_id];

    for (size_t j = 0; j < half; j++)
    {
      row[j] = A[padding + j] + B[padding + j];
    }
  }
}

/**
 * Assigns to the matrix C the difference of two quandrants of A using the given offsets
 */
void sub_inner_submatrices(float *C, const float * A,
                           size_t a_row_start, size_t a_col_start, 
                           size_t b_row_start, size_t b_col_start, 
                           size_t half, size_t size)
{
  size_t padding;
  size_t a_row_id;
  size_t b_row_id;
  const float *a_row;
  const float *b_row;

  for (size_t i = 0; i < half; i++)
  {
    padding = i * half;
    a_row_id = ((a_row_start + i) * size) + a_col_start;
    b_row_id = ((b_row_start + i) * size) + b_col_start;

    a_row = &A[a_row_id];
    b_row = &A[b_row_id];

    for (size_t j = 0; j < half; j++)
    {
      C[padding + j] = a_row[j] - b_row[j];
    }
  }
}

/**
 * Subtracts to the matrix C to the specified quadrant of A
 */
void sub_submatrix(float * C, const float * A, 
              size_t row_start, size_t col_start, 
              size_t half, size_t size)
{
  size_t padding;
  size_t row_id;
  float * row;

  for (size_t i = 0; i < half; i++)
  {
    padding = i * half;
    row_id = ((row_start + i) * size) + col_start;
    row = &C[row_id];

    for (size_t j = 0; j < half; j++)
    {
      row[j] -= A[padding + j];
    }
  }
}

/**
 * Assigns to specified quadrant of C the difference of A and B
 */
void sub_outer_submatrices(float * C, const float * A, const float * B, 
            size_t row_start, size_t col_start, 
            size_t half, size_t size)
{
  size_t padding;
  size_t row_id;
  float * row;

  for (size_t i = 0; i < half; i++)
  {
    padding = i * half;
    row_id = ((row_start + i) * size) + col_start;
    row = &C[row_id];

    for (size_t j = 0; j < half; j++)
    {
      row[j] = A[padding + j] - B[padding + j];
    }
  }
}

/**
 * Copies to C the given quadrant of A
 */
void copy_submatrix(float * C, const float * A,
               size_t row_start, size_t col_start, 
               size_t half, size_t size)
{
  size_t padding;
  size_t row_id;
  const float *row;

  for (size_t i = 0; i < half; i++)
  {
    padding = i * half;
    row_id = ((row_start + i) * size) + col_start;
    row = &A[row_id];

    for (size_t j = 0; j < half; j++)
    {
      C[padding + j] = row[j];
    }
  }
} 

float * strassen_opt(const float * A, const float * B, const size_t size)
{
  if (size < 128)
  {
    return naive_mult(A, B, size);
  }

  size_t half = size / 2;

  /* Top left submatrix */
  size_t tl_row_start = 0;
  size_t tl_col_start = 0;

  /* Top right submatrix */
  size_t tr_row_start = 0;
  size_t tr_col_start = half;

  /* Bottom left submatrix */
  size_t bl_row_start = half;
  size_t bl_col_start = 0;

  /* Bottom right submatrix */
  size_t br_row_start = half;
  size_t br_col_start = half;

  /* The output matrix */
  float * C = (float *)malloc(sizeof(float) * size * size);

  float* AA[7]; /* Submatrix blocks for A */
  float* BB[7]; /* Submatrix blocks for B */
  float* MM[7]; /* Products of above submatrices */
  
  /* Make room for the submatrices */
  for (int i = 0; i < 7; i++)
  {
    AA[i] = (float *)malloc(sizeof(float) * half * half);
    BB[i] = (float *)malloc(sizeof(float) * half * half);
  }

  /* AA[0] = (A1,1 + A2,2) */
  sum_inner_submatrices(AA[0], A, tl_row_start, tl_col_start, br_row_start, br_col_start, half, size);
  /* AA[1] = (A2,1 + A2,2) */
  sum_inner_submatrices(AA[1], A, bl_row_start, bl_col_start, br_row_start, br_row_start, half, size);
  /* AA[2] = (A1,1) */
  copy_submatrix(AA[2], A, tl_row_start, tl_col_start, half, size);
  /* AA[3] = (A2,2) */
  copy_submatrix(AA[3], A, br_row_start, br_col_start, half, size);
  /* AA[4] = (A1,1 + A1,2) */
  sum_inner_submatrices(AA[4], A, tl_row_start, tl_col_start, tr_row_start, tr_col_start, half, size);
  /* AA[5] = (A2,1 - A1,1) */
  sub_inner_submatrices(AA[5], A, bl_row_start, bl_col_start, tl_row_start, tl_col_start, half, size);
  /* AA[6] = (A1,2 - A2,2) */
  sub_inner_submatrices(AA[6], A, tr_row_start, tr_col_start, br_row_start, br_col_start, half, size);

  /* BB[0] = (B1,1 + B2,2) */
  sum_inner_submatrices(BB[0], B, tl_row_start, tl_col_start, br_row_start, br_col_start, half, size);
  /* BB[1] = (B1,1) */
  copy_submatrix(BB[1], B, tl_row_start, tl_col_start, half, size);
  /* BB[2] = (B1,2 - B2,2) */
  sub_inner_submatrices(BB[2], B, tr_row_start, tr_col_start, br_row_start, br_col_start, half, size);
  /* BB[3] = (B2,1 - B1,1) */
  sub_inner_submatrices(BB[3], B, bl_row_start, bl_col_start, tl_row_start, tl_col_start, half, size);
  /* BB[4] = (B2,2) */
  copy_submatrix(BB[4], B, br_row_start, br_col_start, half, size);
  /* BB[5] = (B1,1 + B1,2) */
  sum_inner_submatrices(BB[5], B, tl_row_start, tl_col_start, tr_row_start, tr_col_start, half, size); 
  /* BB[6] = (B2,1 + B2,2) */
  sum_inner_submatrices(BB[6], B, bl_row_start, bl_col_start, br_row_start, br_col_start, half, size);

  MM[0] = strassen_opt(AA[0], BB[0], half);
  MM[1] = strassen_opt(AA[1], BB[1], half);
  MM[2] = strassen_opt(AA[2], BB[2], half);
  MM[3] = strassen_opt(AA[3], BB[3], half);
  MM[4] = strassen_opt(AA[4], BB[4], half);
  MM[5] = strassen_opt(AA[5], BB[5], half);
  MM[6] = strassen_opt(AA[6], BB[6], half);

  /* C1,1 = M1 + M4 - M5 + M7 */
  sum_outer_submatrices(C, MM[0], MM[3], tl_row_start, tl_col_start, half, size);
  sub_submatrix(C, MM[4], tl_row_start, tl_col_start, half, size);
  sum_submatrix(C, MM[6], tl_row_start, tl_col_start, half, size);

  /* C1,2 = M3 + M5 */
  sum_outer_submatrices(C, MM[2], MM[4], tr_row_start, tr_col_start, half, size);

  /* C2,1 = M2 + M4 */
  sum_outer_submatrices(C, MM[1], MM[3], bl_row_start, bl_col_start, half,  size);

  /* C2,2 = M1 - M2 + M3 + M6 */
  sub_outer_submatrices(C, MM[0], MM[1], br_row_start, br_col_start, half, size);
  sum_submatrix(C, MM[2], br_row_start, br_col_start, half, size);
  sum_submatrix(C, MM[5], br_row_start, br_col_start, half, size);

  for (int i = 0; i < 7; i++)
  {
    free (AA[i]);
    free (BB[i]);
    free (MM[i]);
  }
  return C;
}
