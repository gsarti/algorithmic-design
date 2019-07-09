/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Dijkstra algorithms - Header
 * @date 07-07-2019
 */

#ifndef DIJKSTRA_H__
#define DIJKSTRA_H__

#include <iostream>
#include <algorithm>

#include "graph.hpp"
#include "heap.hpp"
#include "utility.hpp"

/**
 * @brief  Initialize the distances and predecessors of the graph
 *         in order to perform Dijkstra algorithm.
 * @param  G  The Graph to be initialized
 */
void graph_init(Graph& G);

/**
 * @brief  Updates distance and predecessors based on available
 *         adjacent nodes.
 * @param  G       The Graph.
 * @param  src     The source node of the graph.
 * @param  dest    The destination node of the graph.
 * @param  weight  The weight src-dest edge.
 */
void relax(Graph& G, int src, int dest, int weight);

/**
 * @brief  Dijkstra's algorithm implementation using
 *         a vector structure. Performs a single source
 *         shortest path search updating distances of Graph G.
 * @param  G    The Graph used for Dijkstra's algo.
 * @param  src  The starting node index.
 */
void dijkstra_vector(Graph& G, int src);

/**
 * @brief  Dijkstra's algorithm implementation using
 *         the Heap class. Performs a single source
 *         shortest path search updating distances of Graph G.
 * @param  G    The Graph used for Dijkstra's algo.
 * @param  src  The starting node index.
 */
void dijkstra_heap(Graph& G, int src);

/**
 * @brief  Auxiliary function for printing paths recursively.
 * @param  G    The Graph to be printed.
 * @param  dest The destination node of the path.
 */
void print_path_rec(Graph G, int dest, int dist);

/**
 * @brief  Prints the path from src to dest.
 * @param  G    The Graph to be printed.
 * @param  src  The source node of the path.
 * @param  dest The destination node of the path.
 */
void print_path(Graph G, int src, int dest);

#endif //DIJKSTRA_H