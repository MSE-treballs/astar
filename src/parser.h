#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <values.h>
#include "nodes.h"
#include "defs.h"

#define FS "|"

size_t read_graph_from_file(FILE *const file, Node **const nodes);
