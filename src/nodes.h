#pragma once
#include "defs.h"

typedef struct Node Node;
typedef struct Node {
    size_t id;
    float lat;
    float lon;
    Bool open;
    float distance;
    Node *parent;
    short n_successors;
    Node **successors;
    float *distances;
    short n_parents;
} Node;

#include "metrics.h"

void print_node(const Node *const node);
size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes);
void add_successor(Node *const node, Node *const successor);
