/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief NodeHeap methods - Source
 * @date 05-07-2019
 */

#include <stdio.h>
#include <limits.h>

#include "heap.h"
#include "../utility.h"

NodeHeap * heap_build(GraphNode * a, size_t size_a, int (*fcomp)(int,int))
{
    GraphNode ** nodes = (GraphNode **)malloc(sizeof(GraphNode *) * size_a);
    for (size_t i = 0; i < size_a; i++)
    {
        a[i].pos = i;
        nodes[i] = &(a[i]);
    }
    NodeHeap H = {H.size = size_a, H.comp = fcomp, H.nodes = nodes};
    for (int i = parent(last(&H)); i >= 0; i--)
    {
        heapify(&H, i);
    }
    return &H;
}

void heap_free(NodeHeap * H)
{
    free(H->nodes);
}

int root()
{
    return 0;
}

int last(NodeHeap * H)
{
    return H->size - 1;
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
    return (i - 1) / 2;
}

int is_root(int i)
{
    return i == root();
}

int heap_is_empty(NodeHeap * H)
{
    return H->size == 0;
}

int heap_is_valid(NodeHeap * H, int i)
{
    return H->size > i;
}

GraphNode * heap_min(NodeHeap * H)
{
    return H->nodes[0];
}

void heap_swap(NodeHeap * H, size_t a, size_t b)
{
    node_swap(H->nodes[a], H->nodes[b]);
}

void heapify(NodeHeap * H, int i)
{
    int val = -1;
    int m = i;

    // Left and right child
    int lc, rc;

    while(m != val)
    {
        val = m;
        rc = right(val);
        lc = left(val);
        m = is_valid(H, lc) && H->comp(H->nodes[lc]->dist, H->nodes[m]->dist) ? lc : m;
	    m = is_valid(H, rc) && H->comp(H->nodes[rc]->dist, H->nodes[m]->dist) ? rc : m;

        if(m != val)
        {
            heap_swap(H, m, val);
        }
    }
}

GraphNode * heap_pop_min(NodeHeap * H)
{
    GraphNode * min = H->nodes[root()];
    H->nodes[root()] = H->nodes[last(H)];
    H->size--;
    heapify(H, root());
    return min;
}

void heap_decrease_key(NodeHeap * H, int i, int val)
{
    H->nodes[i]->dist = val;
    while(!(is_root(i) || H->comp(H->nodes[i]->dist, H->nodes[parent(i)]->dist)))
    {
        heap_swap(H, i, parent(i));
        i = parent(i);
    }
}

void heap_relax(NodeHeap * H, GraphNode * a, GraphNode * b, int d)
{
    if (a->dist + d < b->dist)
    {
        heap_decrease_key(H, b->pos, a->dist + d);
        b->pred = a;
    }
}

void heap_print(NodeHeap * H)
{
    printf("\nHeap size: %d\n", H->size);

    printf("\nNodes: \n");
    for(size_t i = 0; i < H->size; i++)
    {
        node_print(H->nodes[i]);
    }
}