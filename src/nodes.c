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
