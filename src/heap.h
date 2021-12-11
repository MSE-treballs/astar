#pragma once
#include "defs.h"
#include "nodes.h"

typedef struct {
    Node *node;
    float score;
} Element;

typedef struct {
    unsigned capacity;
    unsigned n_elements;
    Element *elements;
} Heap;

Heap *heap_init();
void heap_push(Heap *const heap, Node *const node, const float score);
Node *heap_pop(Heap *const heap);
void heap_replace(Heap *const heap, Node *const node, const float score);
Bool heap_is_empty(const Heap *const heap);
