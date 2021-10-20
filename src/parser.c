#include "parser.h"

void read_graph_from_file(FILE *f) {
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

    Node *nodes = (Node *) malloc(sizeof(Node) * n_nodes);
    if(nodes == NULL) {
        fprintf(stderr, "Not enough memory to store nodes vector with %zu nodes\n", n_nodes);
        return;
    }

    rewind(f);

    // Ignore first three rows of the file
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);
    getline(&line, &line_length, f);

    size_t index = 0;
    while(getline(&line, &line_length, f) > 0) {
        if(line[0] == 'n') {
            size_t pos = 5;
            size_t id = strtoull(line + pos, NULL, 10);

            short counter = 0;
            do {
                do {
                    pos++;
                } while(line[pos] != '|');
                counter++;
            } while(counter < 8);
            pos++;

            double lat = strtod(line + pos, NULL);

            do {
                pos++;
            } while(line[pos] != '|');
            pos++;

            double lon = strtod(line + pos, NULL);

            nodes[index] = (Node) {
                .id = id,
                .lat = lat,
                .lon = lon,
                .n_successors = 0,
                .successors = NULL
            };

            index++;
        } else if(line[0] == 'w') {
            fprintf(stderr, "%s", line);
            size_t pos = 4;
            short counter = 0;
            do {
                do {
                    pos++;
                } while(line[pos] != '|');
                counter++;
            } while(counter < 6);
            pos++;

            Bool oneway = FALSE; // TODO: use
            if(line[pos] == 'o') {
                oneway = TRUE;
            }

            do {
                do {
                    pos++;
                } while(line[pos] != '|');
                counter++;
            } while(counter < 2);
            pos++;

            char *next_id = NULL;
            size_t way_id = strtoull(line + pos, &next_id, 10);
            size_t index_from = search_node(way_id, nodes, n_nodes);

            while(next_id != NULL) {
                size_t way_id = strtoull(next_id + 1, &next_id, 10);
                size_t index_to = search_node(way_id, nodes, n_nodes);

                Node *node = nodes + index_from;

                size_t *tmp = (size_t *) realloc(node->successors, sizeof(size_t) * (node->n_successors + 1));
                if(tmp == NULL) {
                    fprintf(stderr, "Could not allocate enough memory for %zu successors to node %zu\n", node->n_successors + 1, node->id);
                    return;
                }
                node->successors = tmp;

                node->successors[node->n_successors] = index_to;
                node->n_successors++;

                index_from = index_to;
            }

        } else {
            break;
        }
    }
}
