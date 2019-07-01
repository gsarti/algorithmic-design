/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Heap methods - Source
 * @date 30-06-2019
 */

#include <stdio.h>
#include <limits.h>

#include "heap.h"
#include "../utility.h"

BinaryHeap build_heap(int * a, size_t size_a, int (*fcomp)(int,int))
{
    BinaryHeap H = {H.heap = a, H.size = size_a, H.comp = fcomp};
    for (int i = size_a; i >= 0; i--)
    {
        heapify(H, i);
    }
    return H;
}

void free_heap(BinaryHeap H) 
{ 
    free(H.heap); 
}

int root()
{ 
    return 0; 
}

int last(BinaryHeap H) 
{ 
    return H.size - 1;
}

int left(int i) 
{ 
    return 2 * i + 1; 
}

int right(int i) 
{ 
    return 2 * i + 2; 
}

int parent(int i) 
{ 
    return i / 2;
}

int is_root(int i) 
{ 
    return i == root();
}

int is_valid(BinaryHeap H, int i) 
{ 
    return H.size >= i;
}

int heap_min(BinaryHeap H) 
{ 
    return H.heap[root()];
}

void heapify(BinaryHeap H, int i)
{
    int x = i, y = -1;

    // Left and right child
    int lc, rc;

    while(x != y)
    {
        y = x;
        rc = right(x);
        lc = left(x);
	    x = is_valid(H, rc) && H.comp(H.heap[rc], H.heap[x]) ? rc : x;
        x = is_valid(H, lc) && H.comp(H.heap[lc], H.heap[x]) ? lc : x;

        if(y != x)
        {
            swap_int(&(H.heap[i]), &(H.heap[parent(i)]));
        }
    }
}

void heap_decrease_key(BinaryHeap H, int i, int val)
{
    if(H.comp(H.heap[i], val))
    {
        printf("Error: %d should be smaller than the selected element %d", 
               (val, H.heap[i]));
    }

    H.heap[i] = val;
    while(!is_root(i) && H.comp(H.heap[i], H.heap[parent(i)]))
    {
        swap_int(&(H.heap[i]), &(H.heap[parent(i)]));
        i = parent(i);
    }
}

void heap_insert(BinaryHeap H, int val)
{
    H.heap[last(H)] = INT_MAX;
    heap_decrease_key(H, last(H), val);
    H.size++;
}

void heap_print(BinaryHeap H)
{
    printf("\nPrinting Heap with root value: %d", heap_min(H));
    for(int i = 1; i < H.size; i++)
        printf(", %d", H.heap[i]);
    printf("\n");
}