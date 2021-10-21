#include "heap.h"
#include <stdio.h>

void push(PriorityQueue *queue, Node *node, const double score) {
    PriorityQueue *pivot = queue;
    while((pivot != NULL) && (pivot->score < score)) {
        pivot = pivot->next;
    }

    PriorityQueue *tmp = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    tmp->next = pivot->next;
    tmp->node = node;
    tmp->score = score;

    pivot->next = tmp;
}

Node *pop(PriorityQueue **queue) {
    Node *node = (*queue)->node;

    PriorityQueue *tmp = *queue;
    *queue = (*queue)->next;
    free(tmp);

    return node;
}

Bool is_empty(PriorityQueue *queue) {
    return queue == NULL;
}
