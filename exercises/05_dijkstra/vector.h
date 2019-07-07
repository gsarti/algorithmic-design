/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief NodeVector structure to store Graph nodes - Headers
 * @date 04-07-2019
 */

#ifndef VECTOR_H__
#define VECTOR_H__

#include <stdlib.h>

#include "graph.h"

/**
 * @brief A Vector of Nodes
 * @var length  The length of the vector
 * @var nodes   The list of nodes contained in the vector
 */
typedef struct NodeVector
{
    size_t length;
    struct GraphNode ** nodes;
} NodeVector;

// Ctor and dtor for vector
NodeVector * vector_build(GraphNode * a, int size);
void vector_free(NodeVector * V);

int vector_is_empty(NodeVector * V);

int vector_remove(NodeVector * V, int i);

GraphNode * vector_pop_min(NodeVector * V);

int vector_find_node(NodeVector * V, int node_idx);

void vector_relax(NodeVector * V, GraphNode * a, GraphNode * b, int d);

void vector_print(NodeVector * V);

#endif //VECTOR_H