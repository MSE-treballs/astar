#include "priority-queue.h"

PriorityQueue *push(PriorityQueue **const queue, Node *const node, const double score) {
    ASSERT(node != NULL);
    ASSERT(queue != NULL);
    ASSERT(score >= 0);

    node->open = TRUE;

    PriorityQueue *aux = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    ASSERT(aux != NULL);

    *aux = (PriorityQueue) {
        .next = NULL,
        .node = node,
        .score = score,
    };

    if(*queue == NULL) {
        *queue = aux;
        return aux;
    }

    if((*queue)->score > score) {
        aux->next = *queue;
        *queue = aux;
        return aux;
    }

    PriorityQueue *tmp = *queue;
    while((tmp->next != NULL) && (score > tmp->next->score)) {
        tmp = tmp->next;
    }

    aux->next = tmp->next;
    tmp->next = aux;

    return aux;
}

Node *pop(PriorityQueue **const queue) {
    ASSERT(queue != NULL);
    ASSERT((*queue) != NULL);

    Node *node = (*queue)->node;
    node->open = FALSE;

    PriorityQueue *tmp = *queue;
    *queue = (*queue)->next;
    free(tmp);

    return node;
}

void replace(PriorityQueue **const queue, Node *const node, const double score) {
    ASSERT(queue != NULL);
    ASSERT((*queue) != NULL);
    ASSERT(node != NULL);
    ASSERT(score >= 0);

    if((*queue)->node == node) {
        (*queue)->score = score;
        return;
    }

    if((*queue)->score > score) {
        PriorityQueue *removal_point = *queue;

        while(removal_point->next->node != node) {
            removal_point = removal_point->next;
        }

        PriorityQueue *pivot = removal_point->next;
        pivot->score = score;

        removal_point->next = removal_point->next->next;
        pivot->next = *queue;

        *queue = pivot;
        return;
    }

    PriorityQueue *insertion_point = *queue;

    while(insertion_point->next->score < score) {
        insertion_point = insertion_point->next;
    }

    PriorityQueue *removal_point = insertion_point;

    while(removal_point->next->node != node) {
        removal_point = removal_point->next;
    }

    PriorityQueue *pivot = removal_point->next;
    pivot->score = score;

    removal_point->next = removal_point->next->next;
    pivot->next = insertion_point->next;
    insertion_point->next = pivot;
}

Bool is_empty(const PriorityQueue *const queue) {
    return queue == NULL;
}
