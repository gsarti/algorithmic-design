#ifndef GRAPH_H__
#define GRAPH_H__

#include <string>
#include <vector>
#include <iostream>
#include <limits>

#define INT_MAX std::numeric_limits<int>::max()

enum Color { White = 0, Grey = 1, Black = 2 };

struct Node
{
    std::pair<int, int> edge;

    Node() : edge{std::make_pair(0, 0)} {}

    Node(int dest, int weight) : 
        edge{std::make_pair(dest, weight)} {};
    
    int& dest() { return edge.first; }
    int& weight() { return edge.second; }

    void set_dest(int val) { edge.first = val; }
    void set_weight(int val) { edge.second = val; }
};

class Graph
{
private:
    std::vector<Color> colors;
    std::vector<int> predecessors;
    std::vector<int> distances;
    std::vector<std::vector<Node>> adjacents;

public:
    Color get_color(int node_id);
    int get_predecessor(int node_id);
    int get_distance(int node_id);
    int get_weigth(int a, int b);
    int get_adjacent_size();
    std::vector<Node> get_edges(int node_id);
    std::vector<int> get_neighbours(int node_id);

    std::vector<Color>& get_colors();
    std::vector<int>& get_predecessors();
    std::vector<int>& get_distances();
    std::vector<std::vector<Node>>& get_adjacents();

    void set_color(int node_id, Color color);
    void set_predecessor(int node_id, int pred);
    void set_distance(int node_id, int dist);

    void insert_edge(int src, int dest, int weight);
};

#endif //GRAPH_H