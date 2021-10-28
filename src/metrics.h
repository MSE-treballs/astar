#pragma once
#include <math.h>
#include "nodes.h"

double get_distance(const Node *from, const Node *to);
double get_heuristic(const Node *from, const Node *to);
