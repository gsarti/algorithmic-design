#ifndef GRAPH_H__
#define GRAPH_H__

#include "vector.h"

typedef struct GraphNode {
  int dist;
  int idx;
  struct GraphNode *pred;
  int pos;
} GraphNode;

typedef struct Graph {
  struct NodeVector nodes_vec;
  int * weights;
  int size;
} Graph;

Graph graph_build(int * weights, size_t size);

void graph_init(Graph * G);

int graph_get_weight(Graph * G, GraphNode * a, GraphNode * b);

GraphNode * graph_get_node(Graph * G, int id);

NodeVector * graph_get_adjacents(Graph * G, GraphNode * n, int len);

int graph_get_adjacents_size(Graph * G, GraphNode * n);

void graph_print(Graph * G);

#endif //GRAPH_H