#include "astar.h"

Bool astar(Node *node, const size_t n_nodes, const size_t start, const size_t goal) {
    PriorityQueue *queue = NULL;

    const double score = 0;
    push(queue, node + start, score);

    while(!is_empty(queue)) {
        Node *current = pop(&queue);

        if(current->id == goal) {
            return TRUE;
        }

        for(short successor = 0; successor < current->n_successors; successor++) {
            if(is_open(node + successor)) {
                const double score = distance(node + current, node + successor) + heuristic(node + successor, node + goal);
                close(node + successor);
                successor->parent = node;
                push(queue, node + successor, score);
            }
        }
    }

    return FALSE;
}
