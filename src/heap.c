#include "heap.h"
#include <stdio.h>

PriorityQueue *push(PriorityQueue **queue, Node *node, const double score) {
    node->open = FALSE;

    PriorityQueue *aux = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    *aux = (PriorityQueue) {
        .next = NULL,
        .node = node,
        .score = score,
    };

    node->open = TRUE;

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

Node *pop(PriorityQueue **queue) {
    Node *node = (*queue)->node;
    node->open = TRUE;

    PriorityQueue *tmp = *queue;
    *queue = (*queue)->next;
    free(tmp);

    return node;
}

void replace(PriorityQueue **queue, Node *node, const double score) {
    PriorityQueue *aux = push(queue, node, score);

    while(aux->next->node != node) {
        aux = aux->next;
    }

    PriorityQueue *tmp = aux->next;
    aux->next = tmp->next;
    free(tmp);
}

Bool is_empty(PriorityQueue *queue) {
    return queue == NULL;
}
