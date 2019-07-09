# Homework 3: Sorting

* Implement Insertion Sort and Quick Sort.
  
* Implement Heap Sort by using binary heap implementation required by the homework on heaps.
  
* Implement Counting Sort, Radix Sort, and Bucket Sort.

* Implement the Select Algorithm.

* Test the implementations on a set of instances of the problem and evaluate their execution times.

* Prove by testing that both Insertion Sort and Quick Sort take time `O(n^2)` in the worst case.

* Prove by testing that Insertion Sort and Quick Sort take in the best case time `O(n)` and `O(n log n)` respectively.

* Why did we assume that there were no repeated values in A? Generalize the implementation of the Select Algorithm to also deal with repeated values.

## Reproducibility

Implementations of various sorting algorithms are tested inside `main_compare.c`. Executing `compare.x` shows sorting times (in seconds) for all sorting algorithms for appropriate random vectors of various sizes. The column `All Sorted` in the output is a binary value to ensure that the output of all sorting algorithms is indeed a sorted array.

The best and worst cases for Insertion Sort and Quicksort are tested inside `main_edge_cases.c`. Executing `edge_cases.x` shows how executiong time varies from `O(n)` in the worst case to respectively `O(n)` in the best case of Insertion Sort and `O(n log n)` in the best case of Quicksort. The difference in execution time is especially evident for large problem sizes.

The Selection algorithm is tested inside `main_selection.c`. Executing `selection.x` shows selection times (in second) for different problem sizes. The column `Correctness` ensures that the selected value is indeed the i-th value inside the sorted version of the array. The function `partition_balanced` was used inside the Selection algorithm to deal with repeated values.
