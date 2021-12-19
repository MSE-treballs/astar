#include "nodes.h"
#include <stdio.h>
#include <stdlib.h>
#include <values.h>

// python -c "import math; print(180 / math.pi)"
const double RAD_TO_DEG = 57.29577951308232;

void print_node(const Node *const node) {
    ASSERT(node != NULL);

    printf("%zu,%lf,%lf\n", node->id, node->lat * RAD_TO_DEG, node->lon * RAD_TO_DEG);
}

size_t search_node(const size_t id, const Node *const nodes, const size_t n_nodes) {
    ASSERT(nodes != NULL);
    ASSERT(n_nodes > 0);

    size_t low = 0;
    size_t high = n_nodes - 1;

    size_t pivot = (size_t) -1;

    while(low <= high) {
        pivot = (high + low) / 2;
        if(nodes[pivot].id == id) {
            return pivot;
        } else if(nodes[pivot].id < id) {
            low = pivot + 1;
        } else {
            high = pivot - 1;
        }
    }

    return (size_t) -1;
}

void add_successor(Node *const node, Node *const successor) {
    ASSERT(node != NULL);
    ASSERT(successor != NULL);

    for(short iter = 0; iter < node->n_successors; iter++) {
        if(node->successors[iter] == successor) {
            return;
        }
    }

    Node **successors = (Node **) realloc(node->successors, sizeof(Node *) * (node->n_successors + 1));
    if(successors == NULL) {
        fprintf(stderr, "Could not allocate enough memory for %d successors to node %zu\n", node->n_successors + 1, node->id);
        return;
    }
    node->successors = successors;

    double *distances = (double *) realloc(node->distances, sizeof(double) * (node->n_successors + 1));
    if(distances == NULL) {
        fprintf(stderr, "Could not allocate enough memory for %d successors' distances to node %zu\n", node->n_successors + 1, node->id);
        return;
    }
    node->distances = distances;

    node->successors[node->n_successors] = successor;
    node->distances[node->n_successors] = get_distance(node, successor);

    node->n_successors++;
    successor->n_parents++;
}
