# Homework 4: Heaps

* Implement the array-based representation of a binary heap.

* Implement an iterative version of `HEAPIFY`.

* Test the implementation on a set of instances of the problem and evaluate the execution time.

## Reproducibility

The file `main.c` is used to test the array-based representation of a binary heap with an iterative `heapify` function contained in `heap.c` and `heap.h`. Executing `heap.x` generates vectors of `1E8` size that are then passed to the `build_heap` function. Heap building times are estimated for a fixed number of iterations.
