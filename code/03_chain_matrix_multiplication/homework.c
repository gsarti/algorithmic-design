#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

void print_matrix(int ** m, int size)
{
    for(size_t i = 0; i < size; i++)
    {
        for(size_t j = 0; j < size; j++)
        {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int ** allocate_matrix(const int rows, const int cols)
{
   int ** matrix = (int **)malloc(sizeof(int *)*rows);
   for (size_t i = 0; i < rows; i++) 
   {
        matrix[i] = (int *)malloc(sizeof(int)*cols);
   }
   return matrix;
}

void deallocate_matrix(int **A, const size_t rows)
{
  for (size_t i=0; i<rows; i++) {
    free(A[i]);
  }
  free(A);
}

void matrix_chain_aux(int * P, int ** m, int ** s, size_t i, size_t j)
{
    int q = 0;
    m[i][j] = INT_MAX;

    for (size_t k = i; k <= j - 1; k++)
    {
        q = m[i][k] + m[k + 1][j] + P[i] * P[k + 1] * P[j + 1];
        if (q < m[i][j])
        {
            m[i][j] = q;
            s[i][j] = k + 1;
        }
    }
}
  
int matrix_chain(int * P, int n)
{
    int ** m = allocate_matrix(n, n);
    int ** s = allocate_matrix(n, n);

    for (size_t i = 1; i < n; i++)
    {
        m[i][i] = 0;
    }
    for (size_t l = 2; l < n; l++)
    {
        for (size_t i = 0; i < n - l; i++)
        {
            size_t j = i + l - 1;
            matrix_chain_aux(P, m, s, i, j);
        }
    }
    print_matrix(m,n - 1);
    print_matrix(s,n - 1);
    deallocate_matrix(m, n-1);
    deallocate_matrix(s, n-1);
}

int main()
{
    int p[] = {3, 5, 10, 2, 3};
    int n = sizeof(p) / sizeof(p[0]);
    matrix_chain(p, n);

    int p2[] = {10, 100, 20, 5, 80, 7, 22};
    int n2 = sizeof(p2) / sizeof(p2[0]);
    matrix_chain(p2, n2);
    return 0;
}