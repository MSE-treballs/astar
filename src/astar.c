#include "astar.h"
#include <stdio.h>

Bool is_suitable_for_skip(const Node *const node) {
    return (node->n_successors == 1)
        && (node->n_parents == 1)
        && (node->successors[0]->parent == NULL);
}

Bool astar(Node *const start, const Node *const goal) {
    ASSERT(start != NULL);
    ASSERT(goal != NULL);

    Heap *heap = heap_init();

    start->distance = 0;
    heap_push(heap, start, 0);

    while(!heap_is_empty(heap)) {
        Node *current = heap_pop(heap);

        if(current == goal) {
            return TRUE;
        }

        for(short child = 0; child < current->n_successors; child++) {
            Node *successor = current->successors[child];

            double distance = current->distance + get_distance(current, successor);
            if(successor->distance > distance) {
                successor->distance = distance;
                successor->parent = current;

                while((successor != goal) && is_suitable_for_skip(successor)) {
                    distance += get_distance(successor, successor->successors[0]);

                    successor->successors[0]->distance = distance;
                    successor->successors[0]->parent = successor;

                    successor = successor->successors[0];
                }

                const double heuristic = get_heuristic(successor, goal);
                const double score = distance + heuristic;
                if(successor->open == TRUE) {
                    heap_replace(heap, successor, score);
                } else {
                    heap_push(heap, successor, score);
                }
            }
        }
    }

    return FALSE;
}
