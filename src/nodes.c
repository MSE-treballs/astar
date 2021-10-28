#include "nodes.h"

void printNode(const Node *node) {
    printf("node: %zu, lat: %lf lon: %lf n_successors: %zu\n", node->id, node->lat, node->lon, node->n_successors);
}

size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes) {
    size_t low = 0;
    size_t high = n_nodes - 1;

    size_t pivot = -1;

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

    return -1;
}

void add_successor(Node *node, Node *successor) {
    for(short iter = 0; iter < node->n_successors; iter++) {
        if(node->successors[iter] == successor) {
            return;
        }
    }

    Node **tmp = (Node **) realloc(node->successors, sizeof(Node *) * (node->n_successors + 1));
    if(tmp == NULL) {
        fprintf(stderr, "Could not allocate enough memory for %d successors to node %zu\n", node->n_successors + 1, node->id);
        return;
    }

    node->successors = tmp;

    node->successors[node->n_successors] = successor;
    node->n_successors++;
}
