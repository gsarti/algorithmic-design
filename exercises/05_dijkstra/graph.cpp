/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Graph class for Dijkstra's algorithm - Source
 * @date 05-07-2019
 */

#include "graph.hpp"

int Graph::get_predecessor(int node)
{
    return predecessors[node];
}

int Graph::get_distance(int node)
{
    return distances[node];
}

int Graph::get_weigth(int a, int b)
{
    std::vector<Edge> nodes = adjacents[a];
    for (auto node : nodes)
    {
        if (*(node.edge.first) == b)
        {
            return node.edge.second;
        }
    }
    return -1;
}

int Graph::size()
{
    return adjacents.size();
}

std::vector<Edge> Graph::get_edges(int node)
{
    return adjacents[node];
}

std::vector<int> Graph::get_neighbours(int node)
{
    std::vector<int> neigh{};
    for(auto node: get_edges(node))
    {
        neigh.push_back(*(node.edge.first));
    }
    return neigh;
}

std::vector<int>& Graph::get_distances()
{
    return distances;
}

void Graph::set_predecessor(int node, int pred)
{
    predecessors[node] = pred;
}

void Graph::set_distance(int node, int dist)
{
    distances[node] = dist;
}

void Graph::insert_edge(int src, int dest, int weight)
{
    if (adjacents.size() < src + 1)
    {
        for (int i = adjacents.size() - 1; i < src + 1; i++)
        {
            adjacents.push_back(std::vector<Edge>{});
            distances.push_back(INT_MAX);
            predecessors.push_back(-1);
        }
    }
    adjacents[src].push_back(Edge(dest, weight));
}
