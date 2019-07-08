#include "graph.hpp"

Color Graph::get_color(int node_id)
{
    return colors[node_id];
}

int Graph::get_predecessor(int node_id)
{
    return predecessors[node_id];
}

int Graph::get_distance(int node_id)
{
    return distances[node_id];
}

int Graph::get_weigth(int a, int b)
{
    std::vector<Node> nodes = adjacents[a];
    for (auto node : nodes)
    {
        if (*(node.edge.first) == b)
        {
            return node.edge.second;
        }
    }
    return -1;
}

int Graph::get_adjacent_size()
{
    return adjacents.size();
}

std::vector<Node> Graph::get_edges(int node_id)
{
    return adjacents[node_id];
}

std::vector<int> Graph::get_neighbours(int node_id)
{
    std::vector<int> neigh{};
    for(auto node: get_edges(node_id))
    {
        neigh.push_back(*(node.edge.first));
    }
    return neigh;
}

std::vector<Color>& Graph::get_colors()
{
    return colors;
}

std::vector<int>& Graph::get_predecessors()
{
    return predecessors;
}

std::vector<int>& Graph::get_distances()
{
    return distances;
}

std::vector<std::vector<Node>>& Graph::get_adjacents()
{
    return adjacents;
}

void Graph::set_color(int node_id, Color color)
{
    colors[node_id] = color;
}

void Graph::set_predecessor(int node_id, int pred)
{
    predecessors[node_id] = pred;
}

void Graph::set_distance(int node_id, int dist)
{
    distances[node_id] = dist;
}

void Graph::insert_edge(int src, int dest, int weight)
{
    if (adjacents.size() < src + 1)
    {
        for (int i = adjacents.size() - 1; i < src + 1; i++)
        {
            adjacents.push_back(std::vector<Node>{});
            distances.push_back(INT_MAX);
            predecessors.push_back(-1);
            colors.push_back(Color::White);
        }
    }
    adjacents[src].push_back(Node(dest, weight));
}
