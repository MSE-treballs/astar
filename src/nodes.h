#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Node {
    size_t id;
    double lat;
    double lon;
    size_t n_successors;
    Node *successors;
} Node;

void printNode(const Node *node);
