#include "astar.h"
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
    read_graph_from_file(f, &nodes);

    Node *from = nodes + 729630;
    Node *to = nodes + 318042;

    const Bool result = astar(from, to);

    if(result == FALSE) {
        fprintf(stderr, "Could not find path between %zu and %zu\n", from->id, to->id);
        return EXIT_FAILURE;
    }

    Node *tmp = to;
    Node *pv = to->parent;
    Node *ppv;
    to->parent = NULL;
    from->parent = NULL;

    while(tmp != from) {
        ppv=pv->parent;
        pv->parent = tmp;

        tmp = pv;
        pv = ppv;
    }

    tmp = from;
    while(tmp != NULL) {
        print_node_coords(tmp);
        tmp = tmp->parent;
    }

    return 0;
}
