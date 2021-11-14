#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <values.h>
#include "defs.h"

typedef struct Node Node;

typedef struct {
    double cost;
    Node *end;
} Shortcut;

typedef struct Node {
    size_t id;
    double lat;
    double lon;
    Bool open;
    double distance;
    Node *parent;
    short n_successors;
    Node **successors;
    short n_shortcuts;
    Shortcut *shortcuts;
} Node;

#include "metrics.h"

void print_node(const Node *node);
void print_node_coords(const Node *node);
size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes);
void add_successor(Node *node, Node *successor);
void add_shortcut(Node *node, Node *successor);
