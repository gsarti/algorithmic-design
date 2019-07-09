/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Vector structure used for Bucket sort algorithm - Headers
 * @date 01-07-2019
 */

#ifndef VECTOR_H__
#define VECTOR_H__

#include <stdlib.h>

/**
 * @brief A Vector Node
 * @var val   The float value of the node.
 * @var next  The next node in the vector.
 */
typedef struct Node
{
    float val;
    struct Node* next;
} Node;

/**
 * @brief A dynamic Vector of Nodes
 * @var length  The length of the vector
 * @var root    The root node of the vector.
 */
typedef struct Vector
{
    size_t length;
    Node* root;
} Vector;

// Ctor and dtor for node
Node * build_node(float val);
void free_node(Node * node);

// Ctor and dtor for vector
Vector build_vector();
void free_vector(Vector V);

// Retrieve a node and its value
Node * get_node(Vector V, size_t idx);
float get_val(Vector V, size_t idx);

// Appends a new node to the end of the vector
void append(Vector * V, float val);

// Ctor and dtor for a bucket (list of vectors)
Vector* build_bucket(size_t size);
void free_bucket(Vector* B, size_t size);

#endif //VECTOR_H