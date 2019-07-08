/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Dijkstra algorithms - Source
 * @date 07-07-2019
 */

#include "dijkstra.hpp"

void graph_init(Graph& G)
{
    for (size_t i = 0; i < G.get_adjacent_size(); i++)
    {
        G.set_distance(i, INT_MAX);
        G.set_predecessor(i, -1);
    }
}

void relax(Graph& G, int src, int dest, int weight)
{
    int src_dist = G.get_distance(src);
    int dest_dist = G.get_distance(dest);
    if(src_dist + weight < dest_dist)
    {
        G.set_distance(dest, src_dist + weight);
        G.set_predecessor(dest, src);
    }
}

void dijkstra_array(Graph& G, int src)
{
    graph_init(G);
    G.set_distance(src, 0);
    int idx = 0;
    std::vector<int>& dist = G.get_distances();
    std::vector<Node> adj(G.get_adjacent_size());
    for (size_t i = 0; i < G.get_adjacent_size(); i++)
    {
        adj[i].edge.first = &dist[i];
        adj[i].edge.second = i;
    }
    while(idx < G.get_adjacent_size())
    {
        int min = get_min(adj, idx++, G.get_adjacent_size());
        std::vector<int> neighbours = G.get_neighbours(min);
        for(auto node: neighbours)
        {
            int weight = G.get_weigth(min, node);
            relax(G, min, node, weight);
        }
    }
}

void dijkstra_heap(Graph& G, int src)
{
    graph_init(G);
    G.set_distance(src, 0);
    std::vector<int>& dist = G.get_distances();
    std::vector<Node> adj(G.get_adjacent_size());
    for (size_t i = 0; i < G.get_adjacent_size(); i++)
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

void print_path_rec(Graph G, int dest)
{
    if (G.get_predecessor(dest) != -1) {
        print_path_rec(G, G.get_predecessor(dest));
    }
    std::cout << dest << "->";  
}

void print_path(Graph G, int src, int dest)
{
    std::cout << "\nShortest path from " << src << " to " << dest << std::endl;
    print_path_rec(G, G.get_predecessor(dest));
    std::cout << dest << "\tdistance = " << G.get_distance(dest) << std::endl;
}



