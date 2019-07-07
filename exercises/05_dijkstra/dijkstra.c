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
    GraphNode * start = graph_get_node(G, idx);
    start->dist = 0;

    NodeVector * V = vector_build(G->nodes_vec, G->size);
    while(!vector_is_empty(V))
    {
        GraphNode * min = vector_pop_min(V);
        int adj_size = graph_get_adjacents_size(G, min);
        NodeVector * adj = graph_get_adjacents(G, min, adj_size);

        for (size_t i = 0; i < adj_size; i++)
        {
            vector_relax(V, min, adj->nodes[i], 
                         graph_get_weight(G, min, adj->nodes[i]));
        }
        vector_free(adj);
    }
    vector_free(V);
}

void heap_dijkstra(Graph * G, int idx)
{
    GraphNode * start = graph_get_node(G, idx);
    start->dist = 0;

    NodeHeap * H = heap_build(G->nodes_vec, G->size, leq);
    while(!heap_is_empty(H))
    {
        GraphNode * min = heap_pop_min(H);
        int adj_size = graph_get_adjacents_size(G, min);
        NodeVector * adj = graph_get_adjacents(G, min, adj_size);

        for (size_t i = 0; i < adj_size; i++)
        {
            heap_relax(H, min, adj->nodes[i], 
                         graph_get_weight(G, min, adj->nodes[i]));
        }
        vector_free(adj);
    }
    heap_free(H);
}



