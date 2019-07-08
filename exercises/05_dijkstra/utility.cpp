#include "utility.hpp"

void swap(std::vector<Node>& array, int a, int b)
{
    Node temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

int get_min(std::vector<Node> array, int id, int size)
{
    int min = array[id].edge.second;
    for (size_t i = id; i < size; i++)    
    {
        if(*(array[i].edge.first) < min)
        {
            min = array[i].edge.second;
        }
    }
    swap(array, min, id);
    return array[id].edge.second;
}

double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) +
         (e_time.tv_nsec-b_time.tv_nsec)/1E9;
}