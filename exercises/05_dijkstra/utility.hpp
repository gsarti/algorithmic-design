#ifndef UTILITY_H__
#define UTILITY_H__

#include "graph.hpp"

void swap(std::vector<Node>, int a, int b);

int get_min(std::vector<Node>, int start, int size);

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time);


#endif //UTILITY_H