#include "astar.h"

Bool is_suitable_for_skip(const Node *const node) {
    return (node->n_successors == 1)
        && (node->n_parents == 1)
        && (node->successors[0]->parent == NULL);
}

Bool astar(Node *const start, const Node *const goal) {
    ASSERT(start != NULL);
    ASSERT(goal != NULL);

    PriorityQueue *queue = NULL;

    start->distance = 0;
    push(&queue, start, 0);

    while(!is_empty(queue)) {
        Node *current = pop(&queue);

        if(current == goal) {
            return TRUE;
        }

        for(short child = 0; child < current->n_successors; child++) {
            Node *successor = current->successors[child];

            double distance = current->distance + get_distance(current, successor);
            if(successor->distance > distance) {
                successor->distance = distance;
                successor->parent = current;

                while(is_suitable_for_skip(successor) && (successor->successors[0] != goal)) {
                    distance += get_distance(successor, successor->successors[0]);

                    successor->successors[0]->distance = distance;
                    successor->successors[0]->parent = successor;

                    successor = successor->successors[0];
                }

                const double heuristic = get_heuristic(successor, goal);
                const double score = distance + heuristic;
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
