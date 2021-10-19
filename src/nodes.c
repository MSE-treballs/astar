#include "nodes.h"

void printNode(const Node *node) {
    printf("node: %zu, lat: %lf lon: %lf n_successors: %zu\n", node->id, node->lat, node->lon, node->n_successors);
}
