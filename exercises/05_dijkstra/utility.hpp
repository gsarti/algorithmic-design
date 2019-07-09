/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Utility methods for the Dijkstra assignment - Header
 * @date 07-07-2019
 */

#ifndef UTILITY_H__
#define UTILITY_H__

#include "graph.hpp"

// Swaps edges at positions a, b inside an Edge array.
void swap(std::vector<Edge>& array, int a, int b);

// Returns the min weight value in an Edge array.
int pop_min(std::vector<Edge>& array);

// Get execution time.
double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time);


#endif //UTILITY_H