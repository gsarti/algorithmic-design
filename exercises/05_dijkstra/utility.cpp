/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Utility methods for the Dijkstra assignment - Source
 * @date 07-07-2019
 */

#include "utility.hpp"

void swap(std::vector<Edge>& array, int a, int b)
{
    Edge temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int pop_min(std::vector<Edge>& array)
{
    int min = *(array[0].edge.first);
    int idx = 0, pos = 0;
    for (size_t i = 1; i < array.size(); i++)    
    {
        if(*(array[i].edge.first) < min)
        {
            min = *(array[i].edge.first);
            idx = i;
        }
    }
    pos = array[idx].edge.second;
    swap(array, idx, array.size() - 1);
    array.pop_back();
    return pos;
}

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
         (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}