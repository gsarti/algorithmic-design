/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test Dijkstra's algorithms.
 * @date 07-07-2019
 */

#include "dijkstra.hpp"
#include <iostream>
#include <ctime>

#define MAT_SIZE 10000

Graph create_slides_graph()
{
    Graph G_slides{};
    G_slides.insert_edge(0, 1, 1);
    G_slides.insert_edge(0, 2, 5);
    G_slides.insert_edge(1, 5, 15);
    G_slides.insert_edge(2, 3, 2);
    G_slides.insert_edge(3, 4, 1);
    G_slides.insert_edge(4, 5, 3);
    return G_slides;
}

Graph create_book_graph()
{
    Graph G_book{};
    G_book.insert_edge(0, 1, 5);
    G_book.insert_edge(0, 2, 10);
    G_book.insert_edge(1, 3, 2);
    G_book.insert_edge(3, 4, 6);
    G_book.insert_edge(2, 4, 1);
    G_book.insert_edge(1, 2, 3);
    G_book.insert_edge(2, 1, 2);
    G_book.insert_edge(1, 4, 9);
    G_book.insert_edge(3, 0, 7);
    G_book.insert_edge(4, 3, 4);
    return G_book;
}

int main()
{
    struct timespec b_time, e_time;

    Graph G_slides = create_slides_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_array(G_slides, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    std::cout << "Array\t" << get_execution_time(b_time, e_time) << std::endl;

    for (int i = 1; i < G_slides.get_adjacent_size(); i++)
        print_path(G_slides, 0, i);
    
    Graph G_slides2 = create_slides_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_heap(G_slides2, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    std::cout << "Heap\t" << get_execution_time(b_time, e_time) << std::endl;

    for (int i = 1; i < G_slides2.get_adjacent_size(); i++)
        print_path(G_slides2, 0, i);

    Graph G_book = create_book_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_array(G_book, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    std::cout << "Array\t" << get_execution_time(b_time, e_time) << std::endl;

    for (int i = 1; i < G_book.get_adjacent_size(); i++)
        print_path(G_book, 0, i);

    Graph G_book2 = create_book_graph();
    clock_gettime(CLOCK_REALTIME, &b_time);
    dijkstra_heap(G_book2, 0);
    clock_gettime(CLOCK_REALTIME, &e_time);
    std::cout << "Heap\t" << get_execution_time(b_time, e_time) << std::endl;

    for (int i = 1; i < G_book2.get_adjacent_size(); i++)
        print_path(G_book2, 0, i);

    for (int j = 10; j < MAT_SIZE; j = j * 10) {
        Graph G_large_array;
        for (int i = 0; i < j; i++)
        for (int k = 0; k < j; k++) {
            if (abs(i - k) < 3)
            G_large_array.insert_edge(i, k, i * 2 + k * 3 + 4);
            G_large_array.insert_edge(k, i, i + k * 2 + 4);
        }
        Graph G_large_heap{};
        for (int i = 0; i < j; i++)
        for (int k = 0; k < j; k++) {
            if (abs(i - k) < 3)
            G_large_heap.insert_edge(i, k, i * 2 + k * 3 + 4);
            G_large_heap.insert_edge(k, i, i + k * 2 + 4);
        }

        clock_gettime(CLOCK_REALTIME, &b_time);
        dijkstra_array(G_large_array, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        std::cout << "Array of size: " << j << "\tTime: " << get_execution_time(b_time, e_time) << std::endl;

        clock_gettime(CLOCK_REALTIME, &b_time);
        dijkstra_heap(G_large_heap, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        std::cout << "Heap of size: " << j << "\tTime: " << get_execution_time(b_time, e_time) << std::endl;
    }
}