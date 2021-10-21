#include "nodes.h"

void printNode(const Node *node) {
    printf("node: %zu, lat: %lf lon: %lf n_successors: %zu\n", node->id, node->lat, node->lon, node->n_successors);
}

size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes) {
    for(size_t iter = 0; iter < n_nodes; iter++) {
        if(nodes[iter].id == id) {
            return iter;
        }
    }

    return -1;
}

void add_successor(Node *node, const size_t index_to) {
    size_t *tmp = (size_t *) realloc(node->successors, sizeof(size_t) * (node->n_successors + 1));
    if(tmp == NULL) {
        fprintf(stderr, "Could not allocate enough memory for %zu successors to node %zu\n", node->n_successors + 1, node->id);
        return;
    }

    node->successors = tmp;

    node->successors[node->n_successors] = index_to;
    node->n_successors++;
}
