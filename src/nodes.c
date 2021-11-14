#include "nodes.h"

// python -c "import math; print(180 / math.pi)"
const double RAD_TO_DEG = 57.29577951308232;

void print_node(const Node *node) {
    ASSERT(node != NULL);

    printf("node: %zu %lf %lf distance %lf\n", node->id, node->lat * RAD_TO_DEG, node->lon * RAD_TO_DEG, node->distance);
}

void print_node_coords(const Node *node) {
    ASSERT(node != NULL);

    printf("%lf,%lf\n", node->lat * RAD_TO_DEG, node->lon * RAD_TO_DEG);
}

size_t search_node(const size_t id, const Node *nodes, const size_t n_nodes) {
    ASSERT(nodes != NULL);
    ASSERT(n_nodes > 0);

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
    ASSERT(node != NULL);
    ASSERT(successor != NULL);

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

#define MIN_SHORTCUT_LENGTH 3
void add_shortcut(Node *root, Node *successor) {
    ASSERT(root != NULL);
    ASSERT(successor != NULL);
    ASSERT(successor->open == 1);
    ASSERT(successor->n_successors == 1);

    short unsigned length = 0;
    double cost = get_distance(root, successor);
    while((successor->n_successors == 1) && (successor->successors[0]->open == 1)) {
        cost += get_distance(successor, successor->successors[0]);
        successor->successors[0]->parent = successor;
        successor = successor->successors[0];
        length++;
    }
    if(length <= MIN_SHORTCUT_LENGTH) {
        return;
    }

    Shortcut *tmp = (Shortcut *) realloc(root->shortcuts, sizeof(Shortcut) * (root->n_shortcuts + 1));
    if(tmp == NULL) {
        fprintf(stderr, "Could not allocate enough memory for %d shortcuts to node %zu\n", root->n_shortcuts + 1, root->id);
        return;
    }

    root->shortcuts = tmp;

    root->shortcuts[root->n_shortcuts] = (Shortcut) {
        .cost = cost,
        .end = successor,
    };
    root->n_shortcuts++;
}
