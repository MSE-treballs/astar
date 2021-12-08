#include "defs.h"
#include "heap.h"
#include "nodes.h"
#include "metrics.h"

typedef enum {OPEN, CLOSED} Queue;

Bool astar(Node *const start, const Node *const goal);
