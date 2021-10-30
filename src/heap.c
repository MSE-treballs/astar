#include "heap.h"

PriorityQueue *push(PriorityQueue **queue, Node *node, const double score) {
    ASSERT(node != NULL);
    ASSERT(queue != NULL);
    ASSERT(score >= 0);

    node->open = FALSE;

    PriorityQueue *aux = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    ASSERT(aux != NULL);

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
    ASSERT(queue != NULL);
    ASSERT((*queue) != NULL);

    Node *node = (*queue)->node;
    node->open = TRUE;

    PriorityQueue *tmp = *queue;
    *queue = (*queue)->next;
    free(tmp);

    return node;
}

Bool is_empty(PriorityQueue *queue) {
    return queue == NULL;
}
