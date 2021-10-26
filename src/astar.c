#include "astar.h"

Bool astar(Node *nodes, const size_t n_nodes, Node *start, const Node *goal) {
    PriorityQueue *queue = NULL;

    const double score = 0;
    push(&queue, start, score);

    while(!is_empty(queue)) {
        Node *current = pop(&queue);

        if(current == goal) {
            return TRUE;
        }

        for(short foo = 0; foo < current->n_successors; foo++) {
            Node *successor = current->successors[foo];
            const double distance = current->distance + distance(current, successor);
            if(distance < successor->distance) {
                const double heuristic = heuristic(successor, goal);
                const double score = distance + heuristic;
                successor->distance = distance;
                successor->parent = nodes;

                if(successor->open == TRUE) {
                    replace(&queue, successor, score);
                } else {
                    push(&queue, successor, score);
                }
            }
        }
    }

    return FALSE;
}
