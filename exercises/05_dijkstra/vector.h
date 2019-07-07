/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief NodeVector structure to store Graph nodes - Headers
 * @date 04-07-2019
 */

#ifndef VECTOR_H__
#define VECTOR_H__

#include <stdlib.h>

typedef struct GraphNode {
  int dist;
  int idx;
  struct GraphNode *pred;
  int pos;
} GraphNode;

/**
 * @brief A Vector of Nodes
 * @var length  The length of the vector
 * @var nodes   The list of nodes contained in the vector
 */
typedef struct NodeVector
{
    size_t length;
    GraphNode ** nodes;
} NodeVector;

// Ctor
GraphNode * node_build(GraphNode * n, int id);

void node_swap(GraphNode * a, GraphNode * b);

void node_print(GraphNode * n);

// Ctor and dtor for vector
NodeVector vector_build(GraphNode * a, int size);
void vector_free(NodeVector * V);

int vector_is_empty(NodeVector * V);

int vector_remove(NodeVector * V, int i);

GraphNode * vector_pop_min(NodeVector * V);

int vector_find_node(NodeVector * V, int node_idx);

void vector_relax(NodeVector * V, GraphNode * a, GraphNode * b, int d);

void vector_print(NodeVector * V);

#endif //VECTOR_H