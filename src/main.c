#include <time.h>
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

    fclose(f);

    Node *from = nodes + 729630;
    Node *to = nodes + 318042;

    from = (Node *) nodes + 519833;
    to = (Node *) nodes + 461929;

    const clock_t start_time = clock();
    const Bool result = astar(from, to);
    const clock_t end_time = clock();

    const double elapsed_time = ((double) (end_time - start_time)) / ((double) CLOCKS_PER_SEC);
    fprintf(stderr, "A* algorithm run in %lf seconds\n", elapsed_time);
    fprintf(stderr, "Found distance: %lf", to->distance);

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

    printf("lat,lon\n");
    tmp = from;
    while(tmp != NULL) {
        print_node_coords(tmp);
        tmp = tmp->parent;
    }

    return 0;
}
