/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief PairHeap structure to store Graph pairs - Headers
 * @date 05-07-2019
 */

#ifndef HEAP_H__
#define HEAP_H__

#include <iostream>
#include <limits>
#include <memory>

#include "utility.hpp"
#include "graph.hpp"

#define ROOT 0
#define LEFT(i) 2 * i + 1
#define RIGHT(i) 2 * i + 2
#define PARENT(i) (i - 1) / 2

template <class TComp = std::less<int>>
class Heap
{
private:
    std::vector<Node> array;

public:
    TComp comp;

    Heap(std::vector<Node>& array, TComp c = TComp{}) 
        : array{array}, comp{c} {}

    Node& root();
    Node& last();
    Node& left(int i);
    Node& right(int i);
    Node& parent(int i);
    int get_size();
    int heap_min();
    void heapify(int i);
    int pop_min();
    void decrease_key(int i, int val);
    void insert(int val);
    void print();
};

template <class TComp>
Node& Heap<TComp>::root()
{
    return array[ROOT];
}

template <class TComp>
Node& Heap<TComp>::last()
{
    return array[get_size() - 1];
}

template <class TComp>
Node& Heap<TComp>::left(int i)
{
    return array[LEFT(i)];
}

template <class TComp>
Node& Heap<TComp>::right(int i)
{
    return array[RIGHT(i)];
}

template <class TComp>
Node& Heap<TComp>::parent(int i)
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
    return root().weight();
}

template <class TComp>
void Heap<TComp>::heapify(int i)
{
    int val = -1;
    int m = i;

    // Left and right child
    int lc, rc;
    print();
    while(m != val)
    {
        val = m;
        rc = RIGHT(val);
        lc = LEFT(val);
        m = lc < get_size() && comp(left(val).dest(), array[m].dest()) ? lc : m;
	    m = rc < get_size() && comp(right(val).dest(), array[m].dest()) ? rc : m;

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

template <class TComp>
void Heap<TComp>::decrease_key(int i, int val)
{
    int d = array[i].dest();
    d = val;
    while(i != 0 && comp(d, parent(i).dest()))
    {
        swap(array, i, PARENT(i));
        i = PARENT(i);
    }
}

template <class TComp>
void Heap<TComp>::insert(int val)
{
    array.push_back(Node{INT_MAX, -1});
    decrease_key(get_size() - 1, val);
}

template <class TComp>
void Heap<TComp>::print()
{
    std::cout << "Printing Heap with root value: " << heap_min() << std::endl;
    for(auto node : array)
        std::cout << node.dest() << ", " << node.weight() << std::endl;
    std::cout << std::endl;
}

#endif //HEAP_H