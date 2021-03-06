#pragma once
#include "nodes.h"

typedef struct {
    Node *node;
    double score;
} Element;

typedef struct {
    unsigned capacity;
    unsigned n_elements;
    Element *elements;
} Heap;

Heap *heap_init();
void heap_push(Heap *const heap, Node *const node, const double score);
Node *heap_pop(Heap *const heap);
void heap_replace(Heap *const heap, Node *const node, const double score);
Bool heap_is_empty(const Heap *const heap);
