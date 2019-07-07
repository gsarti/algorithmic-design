/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief NodeHeap structure to store Graph nodes - Headers
 * @date 05-07-2019
 */

#ifndef HEAP_H__
#define HEAP_H__

#include <stdlib.h>

#include "graph.h"

/**
 * @brief A Heap of Nodes
 * @var nodes  The list of nodes contained in the heap.
 * @var size   The size of the heap.
 * @var comp   The comparison operator for heap nodes.
 */
typedef struct NodeHeap
{
    struct GraphNode ** nodes;
    size_t size;
    int (* comp) (int, int);
} NodeHeap;

// Ctor and dtor for the heap structure.
NodeHeap * heap_build(GraphNode * a, size_t size_a, int (*fcomp)(int,int));
void heap_free(NodeHeap * H);

// Returns the root node and the last node of the heap.
int root();
int last(NodeHeap * H);

// Return the index of left/right child/parent of i-th node.
int left(int i);
int right(int i);
int parent(int i);

// True if the node at position i is root, false otherwise.
int is_root(int i);

int heap_is_empty(NodeHeap * H);

// True if index i is present in the heap, false otherwise.
int heap_is_valid(NodeHeap * H, int i);

// Returns the value of the root node for the heap.
GraphNode * heap_min(NodeHeap * H);

// Swaps elements at indices i, m of heap H.
void heap_swap(NodeHeap * H, size_t a, size_t b);

// Restores the heap property, auxiliary to build_heap.
void heapify(NodeHeap * H, int i);

// Pops the smallest node in the heap.
GraphNode * heap_pop_min(NodeHeap * H);

// Decreases the key at index i setting it to val, based on comp.
void heap_decrease_key(NodeHeap * H, int i, int val);

void heap_relax(NodeHeap * H, GraphNode * a, GraphNode * b, int d);

// Prints a heap, for debugging purposes.
void heap_print(NodeHeap * H);

#endif //HEAP_H