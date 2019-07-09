/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Graph class for Dijkstra's algorithm - Header
 * @date 05-07-2019
 */

#ifndef GRAPH_H__
#define GRAPH_H__

#include <string>
#include <vector>
#include <iostream>
#include <limits>
#include <memory>

// Used as INFINITY in Dijkstra's pseudocode.
#define INT_MAX std::numeric_limits<int>::max()

/**
 * @brief An Edge structure used for Heap and Graph
 * @var  edge  The pair made by a pointer to a
 *             node and the weight of the edge.
 */
struct Edge
{
    std::pair<int *, int> edge;

    Edge() : edge{std::make_pair(new int(0), 0)} {}

    Edge(int dest, int weight) : 
        edge{std::make_pair(new int(dest), weight)} {};
};

/**
 * @brief  Graph class used to model a graph through
 *         a adjacency matrix of Edge objects.
 * @var  predecessors  Predecessors of each Edge.
 * @var  distances     Distances of each Edge from start.
 * @var  adjacents     Adjacency matrix of Edge objects.
 */
class Graph
{
private:
    std::vector<int> predecessors;
    std::vector<int> distances;
    std::vector<std::vector<Edge>> adjacents;

public:
    // Getter for predecessor of a node.
    int get_predecessor(int node);

    // Getter for distance of a node from start.
    int get_distance(int node);

    // Getter for weight of the edge between two nodes.
    int get_weigth(int a, int b);
    
    // Gets the size of Graph in terms of Edges.
    int size();

    // Get all the edges connected to a node.
    std::vector<Edge> get_edges(int node);

    // Get all neighbours nodes of a node.
    std::vector<int> get_neighbours(int node);

    // Get the distances vector.
    std::vector<int>& get_distances();

    // Sets the predecessor of node to pred.
    void set_predecessor(int node, int pred);

    // Sets the distance of node from start to dist.
    void set_distance(int node, int dist);

    // Add a new edge to the Graph.
    void insert_edge(int src, int dest, int weight);
};

#endif //GRAPH_H