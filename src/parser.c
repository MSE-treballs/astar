#include "parser.h"

void read_graph_from_file(FILE *f) {
    char *line = NULL;
    size_t line_length = 0;

    getline(&line, &line_length, f); // Ignore first three rows of the file
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
}
