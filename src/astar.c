#include "astar.h"

Bool astar(Node *start, Node *goal) {
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

        for(short foo = 0; foo < current->n_successors; foo++) {
            Node *successor = current->successors[foo];

            const double distance = current->distance + get_distance(current, successor);
            if(successor->distance > distance) {
                successor->distance = distance;
                successor->parent = current;

                const double heuristic = get_heuristic(successor, goal);
                const double score = distance + heuristic;
                if(successor->open == TRUE) {
                    replace(&queue, successor, score);
                } else {
                    push(&queue, successor, score);
                }
            }
        }

        for(short foo = 0; foo < current->n_shortcuts; foo++) {
            Shortcut shortcut = current->shortcuts[foo];

            const double distance = current->distance + shortcut.cost;
            Node *end = shortcut.end;
            if(end->distance > distance) {
                end->distance = distance;

                const double heuristic = get_heuristic(end, goal);
                const double score = distance + heuristic;
                if(end->open == TRUE) {
                    replace(&queue, end, score);
                } else {
                    push(&queue, end, score);
                }
            }
        }
    }

    return FALSE;
}
