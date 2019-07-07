/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Main to test Dijkstra's algorithms.
 * @date 07-07-2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

#include "graph.h"
#include "dijkstra.h"
#include "../utility.h"

#define MAT_SIZE 10000

int main()
{
    struct timespec b_time, e_time;

    printf("\nDijkstra in a dense graph:\n");

    printf("Size\t\tHeap\t\tVector\n");
    printf("----\t\t----\t\t------\n");

    for (size_t n = 256; n < MAT_SIZE; n *= 2) 
    {

        int * mat = (int *)malloc(sizeof(int) * n * n);

        for(size_t i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                mat[i * n + j] = (abs(j-i-1)*2+1 + 
                80*((i+j)%3==0))/(1+5*((i+j)%(9)==0));
            }
        }
        Graph G = graph_build(mat, n);

        clock_gettime(CLOCK_REALTIME, &b_time);
        heap_dijkstra(&G, G.size / 2);
        clock_gettime(CLOCK_REALTIME, &e_time);
        double heap_time =  get_execution_time(b_time, e_time);

        clock_gettime(CLOCK_REALTIME, &b_time);
        vector_dijkstra(&G, G.size / 2);
        clock_gettime(CLOCK_REALTIME, &e_time);
        double vec_time =  get_execution_time(b_time, e_time);

        printf("%d\t\t%lf\t\t%lf\n", n, heap_time, vec_time);
        free(mat);
        vector_free(&(G.nodes_vec));
    }

    printf("\nDijkstra in a sparse graph:\n");

    printf("Size\t\tHeap\t\tVector\n");
    printf("----\t\t----\t\t------\n");

    for (size_t n = 256; n < MAT_SIZE; n *= 2) 
    {

        int * mat = (int *)malloc(sizeof(int) * n * n);

        for (size_t i = 0; i < n * n; i++)
        {
            mat[i] = INT_MAX;
        }
        
        for(size_t i = 0; i < n; i++)
        {
            mat[i * n + i + 1] = 33;
        }
        mat[(n - 1) * n] = 33;

        Graph G = graph_build(mat, n);

        clock_gettime(CLOCK_REALTIME, &b_time);
        heap_dijkstra(&G, G.size / 2);
        clock_gettime(CLOCK_REALTIME, &e_time);
        double heap_time =  get_execution_time(b_time, e_time);

        clock_gettime(CLOCK_REALTIME, &b_time);
        vector_dijkstra(&G, G.size / 2);
        clock_gettime(CLOCK_REALTIME, &e_time);
        double vec_time =  get_execution_time(b_time, e_time);

        printf("%d\t\t%lf\t\t%lf\n", n, heap_time, vec_time);
        free(mat);
        vector_free(&(G.nodes_vec));
    }
}