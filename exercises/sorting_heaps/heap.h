#ifndef HEAP_H__
#define HEAP_H__

#include <stdlib.h>

typedef struct BinaryHeap
{
    int * H;
    size_t size;
    int (* comparison) (int, int);
} BinaryHeap;

int left(int i);
int right(int i);
int parent(int i);
int root();
int is_root(int i);
int is_valid(BinaryHeap H, int i);

int heap_min(BinaryHeap H);
void heapify(BinaryHeap H, int i);
void remove_min(BinaryHeap H, int i);

BinaryHeap build_heap(int * A, size_t size);

void heap_decrease_key(BinaryHeap H, int i, int value);
void heap_insert(BinaryHeap H, int value);

/* Extra methods */

void heap_print(BinaryHeap H);

#endif //HEAP_H__