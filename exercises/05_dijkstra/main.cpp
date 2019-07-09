/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test Dijkstra's algorithms correctness and performances.
 * @date 07-07-2019
 */

#include "dijkstra.hpp"
#include <iostream>
#include <ctime>

#define MAT_SIZE 3000

/**
 * @brief Creates a Graph as the one presented in
 *        the course slides, to test for correctness.
 */
Graph create_slides_graph()
{
    Graph G{};
    G.insert_edge(0, 1, 1);
    G.insert_edge(0, 2, 5);
    G.insert_edge(1, 5, 15);
    G.insert_edge(2, 3, 2);
    G.insert_edge(3, 4, 1);
    G.insert_edge(4, 5, 3);
    return G;
}

/**
 * @brief Creates a Graph as the one presented in example here:
 * https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
 * Used to test for correctness.
 */
Graph create_website_graph()
{
    Graph G{};
    G.insert_edge(0, 1, 4);
    G.insert_edge(0, 7, 8);
    G.insert_edge(1, 7, 11);
    G.insert_edge(1, 2, 8);
    G.insert_edge(7, 8, 7);
    G.insert_edge(7, 6, 1);
    G.insert_edge(2, 8, 2);
    G.insert_edge(6, 8, 6);
    G.insert_edge(2, 3, 7);
    G.insert_edge(2, 5, 4);
    G.insert_edge(6, 5, 2);
    G.insert_edge(3, 5, 14);
    G.insert_edge(3, 4, 9);
    G.insert_edge(5, 4, 10);
    return G;
}

/**
 * @brief Creates a dense graph for testing performances.
 * 
 * Weight deliberately taken from Davide Scassola main for
 * Dijkstra assignment to compare with his performances.
 */
Graph create_dense_graph(int size)
{
    Graph G_dense{};
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            G_dense.insert_edge(i, j, (abs(j-i-1)*2+1 + 80*((i+j)%3==0))/(1+5*((i+j)%(9)==0)));
        }
    }
    return G_dense;
}

int main()
{
    struct timespec b_time, e_time;

    Graph G_slides = create_slides_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_vector(G_slides, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    double vec_time = get_execution_time(b_time, e_time);
    std::cout << "Dijkstra Vector:\t" << vec_time << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (int i = 1; i < G_slides.size(); i++)
        print_path(G_slides, 0, i);
    std::cout << std::endl;
    
    G_slides = create_slides_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_heap(G_slides, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    double heap_time = get_execution_time(b_time, e_time);
    std::cout << "Dijkstra Heap: " << heap_time << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (int i = 1; i < G_slides.size(); i++)
        print_path(G_slides, 0, i);
    std::cout << std::endl;

    Graph G_site = create_website_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_vector(G_site, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    vec_time = get_execution_time(b_time, e_time);
    std::cout << "Dijkstra Vector: " << vec_time << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (int i = 1; i < G_site.size(); i++)
        print_path(G_site, 0, i);
    std::cout << std::endl;

    G_site = create_website_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_heap(G_site, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    heap_time = get_execution_time(b_time, e_time);
    std::cout << "Dijkstra Heap:\t" << heap_time << std::endl;
    std::cout << "-----------------------------" << std::endl;

    for (int i = 1; i < G_site.size(); i++)
        print_path(G_site, 0, i);
    std::cout << std::endl;

    std::cout << "Size\t\tVector\t\tHeap\n";
    std::cout << "----\t\t------\t\t----\n";

    for (size_t size = 10; size < MAT_SIZE; size*=2)
    {
        Graph G_dense = create_dense_graph(size);
        clock_gettime(CLOCK_REALTIME, &b_time);
        dijkstra_vector(G_dense, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        vec_time = get_execution_time(b_time, e_time);

        G_dense = create_dense_graph(size);
        clock_gettime(CLOCK_REALTIME, &b_time);
        dijkstra_heap(G_dense, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        heap_time = get_execution_time(b_time, e_time);

        if (size < 1200)
        {
            std::cout << size << "\t\t" << vec_time << "\t" << heap_time << std::endl;
        }
        else
        {
            std::cout << size << "\t\t" << vec_time << "\t\t" << heap_time << std::endl;
        }
        
    }    
}