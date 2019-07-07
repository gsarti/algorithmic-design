/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief NodeVector methods - Source
 * @date 04-07-2019
 */

#include <stdio.h>

#include "vector.h"

NodeVector * vector_build(GraphNode * a, int size)
{
    GraphNode ** nodes = (GraphNode **)malloc(sizeof(GraphNode *) * size);
    if(a != NULL)
    {
        for (size_t i = 0; i < size; i++)
        {
            nodes[i] = &(a[i]);
        }
    }
    NodeVector V = {V.length = size, V.nodes = nodes};
    return &V;
}

void vector_free(NodeVector * V)
{
    free(V->nodes);
}

int vector_is_empty(NodeVector * V)
{
    return V->length == 0;
}

int vector_remove(NodeVector * V, int i)
{
    node_swap(V->nodes[i], V->nodes[V->length - 1]);
    V->length--;
}

GraphNode * vector_pop_min(NodeVector * V)
{
    int min = V->nodes[0]->dist;
    int idx = 0;
    for (size_t i = 0; i < V->length; i++)
    {
        int curr = V->nodes[i]->dist;
        if(curr < min)
        {
            min = curr;
            idx = i;
        }
    }
    GraphNode * n = V->nodes[idx];
    vector_remove(V, idx);
    return n;
}

int vector_find_node(NodeVector * V, int node_idx)
{
    for (size_t i = 0; i < V->length; i++)
    {
        if(V->nodes[i]->idx == node_idx)
        {
            return i;
        }
    }
    return -1;
}

void vector_relax(NodeVector * V, GraphNode * a, GraphNode * b, int d)
{
    if (a->dist + d < b->dist)
    {
        b->dist = a->dist + d;
        b->pred = a;
    }
}

void vector_print(NodeVector * V)
{
    printf("\nVector size: %d\n", V->length);

    printf("\nNodes: \n");
    for(size_t i = 0; i < V->length; i++)
    {
        node_print(V->nodes[i]);
    }
}