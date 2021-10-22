#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Node {
    size_t id;
    double lat;
    double lon;
    size_t n_successors;
    size_t *successors;
} Node;

void printNode(const Node *node);
size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes);
void add_successor(Node *node, const size_t index_to);
