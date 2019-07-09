/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Heap structure and methods - Header
 * @date 29-06-2019
 */

#ifndef HEAP_H__
#define HEAP_H__

#include <stdlib.h>

/**
 * @brief A Binary heap
 * @var heap     A pointer to the array of integers of the heap.
 * @var size  The size of the array of values.
 * @var comp  The comparison function used by the binary heap.
 */
typedef struct BinaryHeap
{
    int * heap;
    size_t size;
    int (* comp) (int, int);
} BinaryHeap;

/**
 * @brief Ctor for the heap structure
 * @param  a       The array of integers to be heapified.
 * @param  size_a  The size of the array.
 * @param  fcomp   The comparison function that should be used as heap property.
 */
BinaryHeap build_heap(int * a, size_t size_a, int (*fcomp)(int,int));

// Dtor for heap structure
void free_heap(BinaryHeap * H);

// Returns the position 0.
int root();

// Returns the position of the last value inside the heap.
int last(BinaryHeap * H);

/** Return the index of left/right child/parent of i-th node.
 *  The heap is mapped to an array structure by putting nodes belonging
 *  to the same level close to each other.
 */
int left(int i);
int right(int i);
int parent(int i);

// True if the node at position i is root, false otherwise.
int is_root(int i);

// True if index i is present in the heap, false otherwise.
int is_valid(BinaryHeap * H, int i);

// Returns the value of the root node for the heap.
int heap_min(BinaryHeap * H);

// Swaps elements at indices i, m of heap H.
void heap_swap(BinaryHeap * H, size_t i, size_t m);

/**
 * @brief Restores the heap property by swapping nodes iteratively
 * Iterative implementation required by the assignment,
 * auxiliary to build_heap and remove_min.
 * 
 * @param  H  The heap to be heapified.
 * @param  i  The index from which the heapification process should start.
 */
void heapify(BinaryHeap * H, int i);

// Pops the smallest node in the heap.
int remove_min(BinaryHeap * H);

// Decreases the key at index i setting it to val, based on comp.
void heap_decrease_key(BinaryHeap * H, int i, int val);

// Inserts a new value in the heap.
void heap_insert(BinaryHeap * H, int val);

// Prints a heap, for debugging purposes.
void heap_print(BinaryHeap * H);

#endif //HEAP_H__