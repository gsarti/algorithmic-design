/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Dijkstra algorithms - Source
 * @date 07-07-2019
 */

#include "heap.h"
#include "graph.h"
#include "vector.h"
#include "dijkstra.h"
#include "../utility.h"

void vector_dijkstra(Graph * G, int idx)
{
    graph_init(G);
    GraphNode * start = graph_get_node(G, idx);
    start->dist = 0;

    NodeVector V = vector_build(*(G->nodes_vec.nodes), G->size);
    NodeVector * v = &V;
    while(!vector_is_empty(v))
    {
        GraphNode * min = vector_pop_min(v);
        int adj_size = graph_get_adjacents_size(G, min);
        NodeVector * adj = graph_get_adjacents(G, min, adj_size);

        for (size_t i = 0; i < adj_size; i++)
        {
            vector_relax(v, min, adj->nodes[i], 
                         graph_get_weight(G, min, adj->nodes[i]));
        }
    }
    vector_free(v);
}

void heap_dijkstra(Graph * G, int idx)
{
    graph_init(G);
    GraphNode * start = graph_get_node(G, idx);
    start->dist = 0;

    NodeHeap H = heap_build(G->nodes_vec, G->size, leq);
    NodeHeap * h = &H;
    while(!heap_is_empty(h))
    {
        GraphNode * min = heap_pop_min(h);
        int adj_size = graph_get_adjacents_size(G, min);
        NodeVector * adj = graph_get_adjacents(G, min, adj_size);
        for (size_t i = 0; i < adj_size; i++)
        {
            GraphNode * n_adj = adj->nodes[i];
            heap_relax(h, min, n_adj, graph_get_weight(G, min, n_adj));
        }
        heapify(h, 0);
    }
    heap_free(h);
}



