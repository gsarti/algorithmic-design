#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "graph.h"
#include "vector.h"
#include "../utility.h"

Graph graph_build(int * weights, size_t size)
{
    Graph G;
    G.weights = weights;
    G.size = size;
    G.nodes_vec = vector_build(NULL, size);
    return G;
}

void graph_init(Graph * G)
{
    for (size_t i = 0; i < G->size; i++)
    {
        G->nodes_vec.nodes[i] = node_build(NULL, i);
    }
}

int graph_get_weight(Graph * G, GraphNode * a, GraphNode * b)
{
    return G->weights[a->idx * G->size + b->idx];
}

GraphNode * graph_get_node(Graph * G, int id)
{
    GraphNode ** nodes = G->nodes_vec.nodes;
    for(size_t i = 0; i < G->size; i++)
    {
        if(nodes[i]->idx == id)
        {
            return nodes[i];
        }
    }
    return NULL;
}

NodeVector * graph_get_adjacents(Graph * G, GraphNode * n, int len)
{
    NodeVector V = vector_build(NULL, len);
    NodeVector * v = &V;
    int idx = 0;
    for (size_t i = 0; i < G->size; i++)
    {
        GraphNode * node = G->nodes_vec.nodes[i];
        int w = graph_get_weight(G, n, node);
        if (w < INT_MAX && node->idx != n->idx)
        {
            v->nodes[idx++] = node;
        }
    }
    return v;
}

int graph_get_adjacents_size(Graph * G, GraphNode * n)
{
    int size = 0;
    for (size_t i = 0; i < G->size; i++)
    {
        GraphNode * node = G->nodes_vec.nodes[i];
        int w = graph_get_weight(G, n, node);
        if (w < INT_MAX && node->idx != n->idx)
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
    vector_print(&(G->nodes_vec));
}

void graph_print_path_rec(Graph * G, GraphNode * dest)
{
    if(dest->pred != NULL)
    {
        graph_print_path_rec(G, dest->pred);
    }
    printf("%d ->", dest->idx);
}

void graph_print_path(Graph * G, int src, int dest)
{
    printf("\nPath from %d to %d\n", src, dest);
    GraphNode * ndest = graph_get_node(G, dest);
    graph_print_path_rec(G, ndest->pred);
    printf("\nTotal distance: %d\n", ndest->dist);
}
