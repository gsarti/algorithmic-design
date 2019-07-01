/**
 * @author Gabriele Sarti (gabriele.sarti996@gmail.com)
 * @brief Vector methods - Source
 * @date 01-07-2019
 */

#include <stdio.h>

#include "vector.h"
#include "../utility.h"

Node * build_node(float val)
{
    Node * n = (Node *)malloc(sizeof(Node));
    n->val = val;
    n->next = NULL;
    return n;
}

void free_node(Node * node)
{
    if (node->next != NULL)
    {
        free_node(node->next);
    }
    free(node);
}

Vector build_vector()
{
    Vector V = {V.length = 0, V.root = NULL};
    return V;
}

void free_vector(Vector V)
{
    if(V.root != NULL)
    {
        free_node(V.root);
    }
}

Node * get_node(Vector V, size_t idx)
{
    Node * cur = V.root;
    for (size_t i = 0; i < idx; i++)
    {
        if(cur->next != NULL)
        {
            cur = cur->next;
        }
    }
    return cur;
}

float get_val(Vector V, size_t idx)
{
    return get_node(V, idx)->val;
}

void append(Vector * V, float val)
{
    if(V->length == 0)
    {
        V->root = build_node(val);
    }
    else
    {
        Node * last = get_node(*V, V->length - 1);
        last->next = build_node(val);
    }
    V->length++;
}

Vector* build_bucket(size_t size)
{
    Vector * B = (Vector *)malloc(sizeof(Vector) * size);
    for (size_t i = 0; i < size; i++)
    {
        B[i] = build_vector();
    }
    return B;
}

void free_bucket(Vector* B, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        free_vector(B[i]);
    }
    free(B);
}