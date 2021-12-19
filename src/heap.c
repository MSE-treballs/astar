#include "defs.h"
#include "heap.h"

const unsigned heap_capacity_start = 1000;
const unsigned heap_capacity_increment = 1000;

void heap_swap(Heap *const heap, const unsigned a, const unsigned b) {
    const Element tmp = heap->elements[b];
    heap->elements[b] = heap->elements[a];
    heap->elements[a] = tmp;
}

Heap *heap_init() {
    Heap *const heap = (Heap *) malloc(sizeof(Heap));
    ASSERT(heap != NULL);

    Element *const elements = (Element *) malloc((heap_capacity_start + 1) * sizeof(Element));
    ASSERT(elements != NULL);

    elements[0] = (Element) {
        .node = NULL,
        .score = 0.0,
    };

    *heap = (Heap) {
        .capacity = heap_capacity_start,
        .n_elements = 0,
        .elements = elements,
    };

    return heap;
}

void heap_increase_capacity(Heap *const heap) {
    heap->capacity += heap_capacity_increment;

    heap->elements = (Element *) realloc(heap->elements, (heap->capacity + 1) * sizeof(Element));
    ASSERT(heap->elements != NULL);
}

void heap_fixup(Heap *const heap, unsigned index) {
    while((index > 1) && (heap->elements[index].score < heap->elements[index / 2].score)) {
        heap_swap(heap, index, index / 2);

        index /= 2;
    }
}

void heap_push(Heap *const heap, Node *const node, const float score) {
    node->open = TRUE;

    if(heap->n_elements == heap->capacity) {
        heap_increase_capacity(heap);
    }

    heap->n_elements++;
    const unsigned index = heap->n_elements;

    heap->elements[index] = (Element) {
        .node = node,
        .score = score,
    };

    heap_fixup(heap, index);
}

void heap_fixdown(Heap *const heap, unsigned index) {
    while(2 * index <= heap->n_elements) {
        unsigned pivot = 2 * index;

        if((pivot < heap->n_elements)
        && (heap->elements[pivot + 1].score < heap->elements[pivot].score)) {
            pivot++;
        }

        if(heap->elements[index].score <= heap->elements[pivot].score) {
            break;
        }

        heap_swap(heap, index, pivot);

        index = pivot;
    }
}

Bool heap_is_empty(const Heap *const heap) {
    return heap->n_elements == 0;
}

Node *heap_pop(Heap *const heap) {
    ASSERT(!heap_is_empty(heap));

    Node *const node = heap->elements[1].node;
    node->open = FALSE;

    heap_swap(heap, 1, heap->n_elements);
    heap->n_elements--;

    heap_fixdown(heap, 1);

    return node;
}

unsigned heap_find_node(const Heap *const heap, Node *const node) {
    for(unsigned index = 1; index < heap->n_elements + 1; index++) {
        if(heap->elements[index].node == node) {
            return index;
        }
    }

    return 0;
}

void heap_replace(Heap *const heap, Node *const node, const float score) {
    const unsigned index = heap_find_node(heap, node);
    ASSERT(index != 0);

    heap->elements[index].score = score;
    heap_fixup(heap, index);
}
