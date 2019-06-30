/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Sorting methods - Header
 * @date 29-06-2019
 */

#ifndef SORTING_H__
#define SORTING_H__

#include <stdio.h>

/* INSERTION SORT */

/**
 * @brief Insertion sort algorithm
 * @param  array  A pointer to the array to be sorted.
 * @param  start  The beginning of the array to be sorted.
 * @param  size   The dimension of the array of integers.
 */
void insertion_sort(float * array, size_t start, size_t size);
void insertion_sort_int(int * array, size_t start, size_t size);

/* QUICKSORT */

/**
 * @brief Partitions an array of elements into two sets,
 *        one smaller and one greater than the pivot. 
 *        Used for Quicksort.
 * @param  A      A pointer to the array of integers to be sorted.
 * @param  low    The lower bound index of the array.
 * @param  high   The upper bound index of the array. 
 * @param  pivot  The index of the value used as pivot.
 * @return int    The index of the pivot after the partitioning.
 */
int partition(int * A, size_t low, size_t high, size_t pivot);

/**
 * @brief Recursive quicksort auxiliary method.
 * @param  A              A pointer to the array of integers to be sorted.
 * @param  low            The lower bound index of the array.
 * @param  high           The upper bound index of the array.
 * @param  central_pivot  If True, uses central array value as pivot.
 */
void quicksort_rec(int * A, size_t low, size_t high, int central_pivot);

/**
 * @brief Quicksort algorithm
 * @param  array  A pointer to the array to be sorted.
 * @param  start  The beginning of the array to be sorted.
 * @param  size   The dimension of the array.
 * @param  central_pivot  If True, uses central array value as pivot.
 */
void quicksort(int * array, size_t start, size_t size, int central_pivot);

/* HEAPSORT */

/**
 * @brief Heapsort algorithm
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  size   The dimension of the array of integers.
 */
void heapsort(int * array, size_t size);

#endif //SORTING_H__