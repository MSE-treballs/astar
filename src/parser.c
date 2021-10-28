#include "parser.h"
#include <values.h>

// python -c "import math; print(math.pi / 180)"
const double DEG_TO_RAD = 0.017453292519943295;

size_t read_graph_from_file(FILE *f, Node **nodes_vector) {
    char *line = NULL;
    size_t line_length = 0;

    // Ignore first three rows of the file
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);

    size_t n_nodes = 0;
    while(getline(&line, &line_length, f) > 0) {
        if(line[0] == 'n') {
            n_nodes++;
        } else {
            break;
        }
    }

    size_t n_ways = 1;
    while(getline(&line, &line_length, f) > 0) {
        if(line[0] == 'w') {
            n_ways++;
        } else {
            break;
        }
    }

    Node *nodes = (Node *) malloc(sizeof(Node) * n_nodes);
    if(nodes == NULL) {
        fprintf(stderr, "Not enough memory to store nodes vector with %zu nodes\n", n_nodes);
        free(line);
        return 0;
    }
    *nodes_vector = nodes;

    rewind(f);

    // Ignore first three rows of the file
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);

    for(size_t iter = 0; iter < n_nodes; iter++) {
        getline(&line, &line_length, f);

        char *next_field = line + 5;

        size_t id = strtoull(next_field, &next_field, 10);
        next_field++;

        for(size_t foo = 0; foo < 7; foo++) {
            strsep(&next_field, FS);
        }

        double lat = strtod(next_field, &next_field);
        next_field++;

        double lon = strtod(next_field, &next_field);

        nodes[iter] = (Node) {
            .id = id,
            .lat = lat * DEG_TO_RAD,
            .lon = lon * DEG_TO_RAD,
            .open = FALSE,
            .distance = MAXFLOAT,
            .parent = NULL,
            .n_successors = 0,
            .successors = NULL,
        };
    }

    for(size_t iter = 0; iter < n_ways; iter++) {
        getline(&line, &line_length, f);

        char *next_field = line + 4;

        for(size_t foo = 0; foo < 6; foo++) {
            strsep(&next_field, FS);
        }

        Bool oneway = FALSE;
        if(*next_field == 'o') {
            oneway = TRUE;
        }

        strsep(&next_field, FS);
        strsep(&next_field, FS);

        size_t node_id = strtoull(next_field, &next_field, 10);
        size_t index_from = search_node(node_id, nodes, n_nodes);

        while((*next_field != '\n') && (index_from == (size_t) -1)) {
            node_id = strtoull(next_field + 1, &next_field, 10);
            index_from = search_node(node_id, nodes, n_nodes);
        }

        while(*next_field != '\n') {
            node_id = strtoull(next_field + 1, &next_field, 10);
            size_t index_to = search_node(node_id, nodes, n_nodes);

            if(index_to == (size_t) -1) {
                continue;
            }

            add_successor(nodes + index_from, index_to);
            if(oneway == FALSE) {
                add_successor(nodes + index_to, index_from);
            }

            index_from = index_to;
        }
    }

    free(line);
    return n_nodes;
}
