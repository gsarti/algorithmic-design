/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Heap structure used to store Edges of a Graph
 *        Header & Source (Templated Class)
 * @date 05-07-2019
 */

#ifndef HEAP_H__
#define HEAP_H__

#include <iostream>
#include <limits>
#include <memory>

#include "utility.hpp"
#include "graph.hpp"

// Idx of the base Edge inside the heap.
#define ROOT 0

// Idx of the left child of Edge i.
#define LEFT(i) 2 * i + 1

// Idx of the right child of Edge i.
#define RIGHT(i) 2 * i + 2

// Idx of the parent of Edge i.
#define PARENT(i) (i - 1) / 2

/**
 * @brief Heap structure to store adjacency vectors for each node.
 * @tparam  The heap can be templated with a comparison operator.
 *          std::less_equal<int> is used as default (min heap).
 * @var  array  The adjacency vector of Edge objects.
 * @var  comp   The comparison operator used for the heap property.  
 */
template <class TComp = std::less_equal<int>>
class Heap
{
private:
    std::vector<Edge> array;

public:
    TComp comp;

    Heap(std::vector<Edge>& array, TComp c = TComp{}) 
        : array{array}, comp{c} {}

    // Get the root Edge of the array.
    Edge& root();

    // Get the last Edge of the array.
    Edge& last();

    // Get the left Edge of the i-th Edge.
    Edge& left(int i);

    // Get the right Edge of the i-th Edge.
    Edge& right(int i);

    // Get the parent Edge of the i-th Edge.
    Edge& parent(int i);

    // Get the heap size;
    int get_size();

    // Get the weight of the root Edge in the heap.
    int heap_min();

    // Restores the heap property for edges.
    void heapify(int i);

    // Removes the root Edge from the heap and returns its weight.
    int pop_min();
};

template <class TComp>
Edge& Heap<TComp>::root()
{
    return array[ROOT];
}

template <class TComp>
Edge& Heap<TComp>::last()
{
    return array[get_size() - 1];
}

template <class TComp>
Edge& Heap<TComp>::left(int i)
{
    return array[LEFT(i)];
}

template <class TComp>
Edge& Heap<TComp>::right(int i)
{
    return array[RIGHT(i)];
}

template <class TComp>
Edge& Heap<TComp>::parent(int i)
{
    return array[PARENT(i)];
}

template <class TComp>
int Heap<TComp>::get_size()
{
    return array.size();
}

template <class TComp>
int Heap<TComp>::heap_min()
{
    return root().edge.second;
}

template <class TComp>
void Heap<TComp>::heapify(int i)
{
    int val = -1;
    int m = i;

    // Left and right child
    int lc, rc;
    while(m != val)
    {
        val = m;
        rc = RIGHT(val);
        lc = LEFT(val);
        m = lc < get_size() && comp(*(left(val).edge.first), *(array[m].edge.first)) ? lc : m;
	    m = rc < get_size() && comp(*(right(val).edge.first), *(array[m].edge.first)) ? rc : m;

        if(m != val)
        {
            swap(array, m, val);
        }
    }
}

template <class TComp>
int Heap<TComp>::pop_min()
{
    int min = heap_min();
    array[ROOT] = last();
    array.pop_back();
    return min;
}

#endif //HEAP_H