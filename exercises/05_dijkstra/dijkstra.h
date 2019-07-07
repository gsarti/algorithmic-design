/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Dijkstra algorithms - Header
 * @date 07-07-2019
 */

#ifndef DIJKSTRA_H__
#define DIJKSTRA_H__

#include "graph.h"

void vector_dijkstra(Graph * G, int idx);

void heap_dijkstra(Graph * G, int idx);

#endif //DIJKSTRA_H