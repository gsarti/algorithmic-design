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
 * @var H     A pointer to the array of integers of the heap.
 * @var size  The size of the array of values.
 * @var comp  The comparison function used by the binary heap.
 */
typedef struct BinaryHeap
{
    int * H;
    size_t size;
    int (* comp) (int, int);
} BinaryHeap;

// Ctor and dtor for the heap structure.
BinaryHeap build_heap(int * A, size_t size_a, int (*fcomp)(int,int));
void free_heap(BinaryHeap H);

// Returns the root node and the last node of the heap.
int root();
int last(BinaryHeap H);

// Return the index of left/right child/parent of i-th node.
int left(int i);
int right(int i);
int parent(int i);

// True if the node at position i is root, false otherwise.
int is_root(int i);

// True if index i is present in the heap, false otherwise.
int is_valid(BinaryHeap H, int i);

// Returns the value of the root node for the heap.
int heap_min(BinaryHeap H);

// Restores the heap property, auxiliary to build_heap.
void heapify(BinaryHeap H, int i);

// Removes the minimal value in the heap based on comp.
void remove_min(BinaryHeap H, int i);

// Decreases the key at index i setting it to val, based on comp.
void heap_decrease_key(BinaryHeap H, int i, int val);

// Inserts a new value in the heap.
void heap_insert(BinaryHeap H, int value);

/* Extra methods */

// Prints a heap, for debugging purposes.
void heap_print(BinaryHeap H);

#endif //HEAP_H__