/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Dijkstra algorithms - Source
 * @date 07-07-2019
 */

#include "dijkstra.hpp"

void graph_init(Graph& G)
{
    for (size_t i = 0; i < G.size(); i++)
    {
        G.set_distance(i, INT_MAX);
        G.set_predecessor(i, -1);
    }
}

void relax(Graph& G, int src, int dest, int weight)
{
    size_t src_dist = G.get_distance(src);
    size_t dest_dist = G.get_distance(dest);
    if(src_dist + weight < dest_dist)
    {
        G.set_distance(dest, src_dist + weight);
        G.set_predecessor(dest, src);
    }
}

void dijkstra_vector(Graph& G, int src)
{
    graph_init(G);
    G.set_distance(src, 0);
    int idx = 0;
    std::vector<int>& dist = G.get_distances();
    std::vector<Edge> adj(G.size());
    for (size_t i = 0; i < G.size(); i++)
    {
        adj[i].edge.first = &dist[i];
        adj[i].edge.second = i;
    }
    while(adj.size() != 0)
    {
        int min = pop_min(adj);
        for(auto node: G.get_neighbours(min))
        {
            relax(G, min, node, G.get_weigth(min, node));
        }
    }
}

void dijkstra_heap(Graph& G, int src)
{
    graph_init(G);
    G.set_distance(src, 0);
    std::vector<int>& dist = G.get_distances();
    std::vector<Edge> adj(G.size());
    for (size_t i = 0; i < G.size(); i++)
    {
        adj[i].edge.first = &dist[i];
        adj[i].edge.second = i;
    }
    Heap<std::less_equal<int>> H = Heap<std::less_equal<int>>(adj);
    while(H.get_size() != 0)
    {
        int min = H.pop_min();
        for(auto node: G.get_neighbours(min))
        {
            relax(G, min, node, G.get_weigth(min, node));
        }
        H.heapify(0);
    }
}

void print_path_rec(Graph G, int dest, int dist)
{
    if (G.get_predecessor(dest) != -1) {
        print_path_rec(G, G.get_predecessor(dest), G.get_distance(dest));
    }
    std::cout << dest << "-(" << dist << ")->";  
}

void print_path(Graph G, int src, int dest)
{
    std::cout << "Shortest path from " << src << " to " << dest << ": ";
    print_path_rec(G, G.get_predecessor(dest), G.get_distance(dest));
    std::cout << dest << std::endl;
}



