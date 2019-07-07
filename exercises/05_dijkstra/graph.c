#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "vector.h"

GraphNode * node_build(int id)
{
    GraphNode * n = {n->dist = INT_MAX, n->idx = id, n->pred = NULL};
    return n;
}

void node_swap(GraphNode * a, GraphNode * b)
{
    GraphNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void node_print(GraphNode * n)
{
    printf("\nIdx: %d, Dist: %d", n->idx, n->dist);
    if(n->pred != NULL)
        printf(", Pred Idx: %d\n", n->pred->idx);
    else
        printf(", No Pred\n");
}

Graph * graph_build(int * weights, size_t size)
{
    Graph G = {G.weights = weights, 
               G.size = size};
    G.nodes_vec = vector_build(NULL, size);
    graph_init(&G);
    return &G;
}

void graph_init(Graph * G)
{
    for (size_t i = 0; i < G->size; i++)
    {
        G->nodes_vec->nodes[i] = node_build(i);
    }
}

int graph_get_weight(Graph * G, GraphNode * a, GraphNode * b)
{
    return G->weights[a->idx * G->size + b->idx];
}

GraphNode * graph_get_node(Graph * G, int i)
{
    GraphNode ** nodes = G->nodes_vec->nodes;
    for(size_t i = 0; i < G->size; i++)
    {
        if(nodes[i]->idx == i)
        {
            return nodes[i];
        }
    }
    return NULL;
}

NodeVector * graph_get_adjacents(Graph * G, GraphNode * n, int len)
{
    NodeVector * V = vector_build(NULL, len);
    int idx = 0;
    for (size_t i = 0; i < G->size; i++)
    {
        GraphNode * node = G->nodes_vec->nodes[i];
        int w = graph_get_weight(G, n, node);
        if (w != INT_MAX && node->idx != n->idx)
        {
            V->nodes[idx++] = node;
        }
    }
    return V;
}

int graph_get_adjacents_size(Graph * G, GraphNode * n)
{
    int size = 0;
    for (size_t i = 0; i < G->size; i++)
    {
        GraphNode * node = G->nodes_vec->nodes[i];
        int w = get_weight(G, n, node);
        if (w != INT_MAX && node->idx != n->idx)
        {
            size++;
        }
    }
    return size;
}

void graph_print(Graph * G)
{
    printf("\nGraph size: %d\n", G->size);
    printf("\nWeights: \n");

    for(size_t i = 0; i < G->size; i++)
    {
        for(size_t j = 0; j < G->size; j++)
        {
            int curr = G->weights[G->size * i + j];
            if(curr == INT_MAX)
                printf("INF ");
            else 
                printf("%d ", curr);
        }
        printf("\n");
    }

    printf("\nNodes: \n");
    for(size_t i = 0; i < G->size; i++)
    {
        vector_print(G->nodes_vec);
    }
}
