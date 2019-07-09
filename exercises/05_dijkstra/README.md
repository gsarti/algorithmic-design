# Homework 5: Weighted Graphs

* Implement the array-based version of the Dijkstra's algorithm

* Implement the binary heap-based version of the Dijkstra's algorithm.

* Test the implementations on a set of instances of the problem and compare their execution times.

## Disclaimer

For this assignment only, C++ and the `vector` structure were used in order to reduce the complexity of managing memory, since a first approach in C with a custom vector class proved unsuccessful and made me lose a lot of time.
In order to avoid problems of interoperability between C and C++, the `Heap` class and the `utility` methods for this exercise were rewritten in C++ and adapted to the assignment tasks.

## Reproducibility

The file `main.cpp` contains the tests for the Dijkstra algorithm implementations using a vector and a heap. Executing `dijkstra.x` first tests the validity of the two apporaches by comparing their results with reliable sources on two toy problems (one presented in course slides, one found [here](https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/)). After that, a benchmark for dense simil-random graphs is performed to compare the performances of the two approaches. Sadly, with my implementation we don't observe any improvement in terms of execution time for the heap-based approach. This is probably due to the operations performed inside the `Heap` class not being optimal.
