/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Dijkstra algorithms - Header
 * @date 07-07-2019
 */

#ifndef DIJKSTRA_H__
#define DIJKSTRA_H__

#include <iostream>
#include <list>

#include "graph.hpp"
#include "heap.hpp"
#include "utility.hpp"

void graph_init(Graph& G);

void relax(Graph& G, int src, int dest, int weight);

void dijkstra_array(Graph& G, int src);

void dijkstra_heap(Graph& G, int src);

void print_path_rec(Graph G, int dest);

void print_path(Graph G, int src, int dest);

#endif //DIJKSTRA_H