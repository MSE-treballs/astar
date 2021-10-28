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
    size_t n_successors;
    Node **successors;
} Node;

void printNode(const Node *node);
size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes);
void add_successor(Node *node, const size_t index_to);
