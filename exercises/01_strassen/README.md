# Homework 1: Matrix Multiplication

Compile the provided code using `cc -O4 -o strassen_test  *.c`, then improve the implementation of the Strassen’s algorithm by reducing the memory allocations and test the effects on the execution time.

## Reproducibility

Executing `strassen.x` will print the execution times for the naive matrix-matrix product (column `Naive`), the provided Strassen implementation (column `Strassen`) and the optimized Strassen implementation we had to create (column `Strassen Opt.`) for various matrix sizes. The column `Correctness` is a boolean value to test equality of the results.

We can observe that the optimized strassen implementation is consistently better than the regular one time-wise for large problem sizes, due to optimized memory usage and allocation.
