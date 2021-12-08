#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include "defs.h"

typedef struct Node Node;

typedef struct Node {
    size_t id;
    double lat;
    double lon;
    Bool open;
    double distance;
    Node *parent;
    short n_successors;
    Node **successors;
    short n_parents;
} Node;

#include "metrics.h"

void print_node(const Node *const node);
void print_node_coords(const Node *const node);
size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes);
void add_successor(Node *const node, Node *const successor);
