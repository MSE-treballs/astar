#pragma once
#include "defs.h"
#include "nodes.h"

typedef struct PriorityQueue PriorityQueue;
typedef struct PriorityQueue {
    PriorityQueue *next;
    Node *node;
    double score;
} PriorityQueue;

PriorityQueue *push(PriorityQueue **queue, Node *node, const double score);
Node *pop(PriorityQueue **queue);
void replace(PriorityQueue **queue, Node *node, const double score);
Bool is_empty(PriorityQueue *queue);
