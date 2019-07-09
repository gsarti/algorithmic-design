/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Sorting methods - Header
 * @date 29-06-2019
 */

#ifndef SORTING_H__
#define SORTING_H__

#include <stdio.h>

#include "vector.h"

/* INSERTION SORT */

/**
 * @brief Insertion sort algorithm
 * @param  array  A pointer to the array to be sorted.
 * @param  start  The beginning of the array to be sorted.
 * @param  size   The dimension of the array of integers.
 */
void insertion_sort(int * array, size_t size);
void insertion_sort_float(float * array, size_t start, size_t size);
void insertion_sort_int(int * array, size_t start, size_t size);

// Performs insertion sort on a vector of nodes.
void insertion_sort_vector(Vector * v);

/* QUICKSORT */

/**
 * @brief Partitions an array of elements into two sets,
 *        one smaller and one greater than the pivot. 
 *        Used for Quicksort.
 * @param  array      A pointer to the array of integers to be sorted.
 * @param  low        The lower bound index of the array.
 * @param  high       The upper bound index of the array. 
 * @param  pivot_idx  The index of the pivot value used for partition.
 * @return int    The index of the pivot after the partitioning.
 */
int partition(int * array, size_t low, size_t high, size_t pivot_idx);

/**
 * @brief Recursive quicksort auxiliary method.
 * @param  array    A pointer to the array of integers to be sorted.
 * @param  low      The lower bound index of the array.
 * @param  high     The upper bound index of the array. 
 * @param  central  If 1, uses the central pivot, else uses low.
 */
void quicksort_rec(int * array, size_t low, size_t high, size_t central);

/**
 * @brief Quicksort algorithm
 * @param  array      A pointer to the array of integers to be sorted.
 * @param  size       The size of the array to be sorted.
 * @param  pivot_idx  The index of the pivot value used for partition.
 * @param  central  If 1, uses the central pivot, else uses low.
 */
void quicksort(int * array, size_t size, size_t central);

/* HEAPSORT */

/**
 * @brief Heapsort algorithm.
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  size   The dimension of the array of integers.
 */
void heapsort(int * array, size_t size);

/* COUNTING SORT */

/**
 * @brief Counting sort algorithm.
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  size   The dimension of the array of integers.
 * @param  bound  The upper bound for the domain of values in array.
 */
void counting_sort(int * array, size_t size, size_t bound);

/* RADIX SORT */

/**
 * @brief Radix sort algorithm.
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  size   The dimension of the array of integers.
 */
void radix_sort(int * array, size_t size);

/* BUCKET SORT */

/**
 * @brief Bucketsort algorithm.
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  size   The dimension of the array of integers.
 * 
 * Linear complexity for sorting numbers in a uniform distribution in [0,1).
 */
void bucket_sort(float * array, size_t size);

/* SELECT ALGORITHM */

/**
 * @brief Partition algorithm tuned for balancing repeated values.
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  low    The lower bound index of the array.
 * @param  high   The upper bound index of the array. 
 * @param  pivot  The index of the pivot value used for partition.
 * @return int    The index of the pivot after the partitioning.
 */
int partition_balanced(int * array, size_t low, size_t high, size_t pivot);

/**
 * @brief  Selects a pivot in an optimized way for repeated values
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  low    The lower bound index of the array.
 * @param  high   The upper bound index of the array. 
 * @return int    The index of the pivot.
 */
int select_pivot(int * array, size_t low, size_t high);

/**
 * @brief  Selects the i-th sorted value of the array without sorting it.
 * @param  array  A pointer to the unsorted array of integers to be searched.
 * @param  low    The lower bound index of the array.
 * @param  high   The upper bound index of the array. 
 * @param  i      The index of the value in the sorted array.
 * @return int    The value of the i-th sorted value.
 */
int selection(int * array, size_t low, size_t high, size_t i);

#endif //SORTING_H__