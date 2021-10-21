#include "parser.h"

size_t read_graph_from_file(FILE *f, Node **nodes_vector) {
    Node *nodes = *nodes_vector;
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
    printf("n_nodes=%zu\n", n_nodes);

    nodes = (Node *) malloc(sizeof(Node) * n_nodes);
    if(nodes == NULL) {
        fprintf(stderr, "Not enough memory to store nodes vector with %zu nodes\n", n_nodes);
        free(line);
        return 0;
    }

    rewind(f);

    // Ignore first three rows of the file
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);

    size_t index = 0;
    while(getline(&line, &line_length, f) > 0) {
        if(line[0] == 'n') {
            char *next_field = line + 5;

            size_t id = strtoull(next_field, &next_field, 10);
            next_field++;

            for(size_t iter = 0; iter < 7; iter++) {
                strsep(&next_field, FS);
            }

            double lat = strtod(next_field, &next_field);
            next_field++;

            double lon = strtod(next_field, &next_field);

            nodes[index] = (Node) {
                .id = id,
                .lat = lat,
                .lon = lon,
                .n_successors = 0,
                .successors = NULL
            };

            index++;
        } else if(line[0] == 'w') {
            char *next_field = line + 4;

            for(size_t iter = 0; iter < 6; iter++) {
                strsep(&next_field, FS);
            }

            Bool oneway = FALSE;
            if(*next_field == 'o') {
                oneway = TRUE;
            }

            strsep(&next_field, FS);

            size_t way_id = strtoull(next_field + 1, &next_field, 10);
            size_t index_from = search_node(way_id, nodes, n_nodes);

            while((*next_field != '\n') && (index_from == (size_t) -1)) {
                way_id = strtoull(next_field + 1, &next_field, 10);
                index_from = search_node(way_id, nodes, n_nodes);
            }

            while(*next_field != '\n') {
                way_id = strtoull(next_field + 1, &next_field, 10);
                size_t index_to = search_node(way_id, nodes, n_nodes);

                if(index_to == (size_t) -1) {
                    continue;
                }

                add_successor(nodes + index_from, index_to);
                if(oneway == FALSE) {
                    add_successor(nodes + index_to, index_from);
                }

                index_from = index_to;
            }
        } else {
            break;
        }
    }

    free(line);
    return n_nodes;
}
