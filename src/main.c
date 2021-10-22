#include <stdio.h>
#include "parser.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage:\n\t%s <map data>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        fprintf(stderr, "Could not find file \"%s\"\n", argv[1]);
        return 2;
    }

    Node *nodes = NULL;
    size_t n_nodes = read_graph_from_file(f, &nodes);

    return 0;
}
