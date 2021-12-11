#include "astar.h"
#include "defs.h"
#include "nodes.h"
#include "parser.h"
#include <time.h>

int main(int argc, char *argv[]) {
    if((argc != 2) && (argc != 4)) {
        fprintf(stderr, "Usage:\n\t%s <map data> [<start-id>] [<goal-id>]\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(f == NULL) {
        fprintf(stderr, "Could not find file \"%s\"\n", argv[1]);
        return 2;
    }

    Node *nodes = NULL;
    const size_t n_nodes = read_graph_from_file(f, &nodes);
    fclose(f);

    Node *start = nodes + 519833;
    Node *goal = nodes + 461929;

    if(argc == 4) {
        const size_t start_index = search_node(strtoull(argv[2], NULL, 10), nodes, n_nodes);
        if(start_index == (size_t) -1) {
            fprintf(stderr, "Could not find start node with id %s\n", argv[2]);
            return 3;
        }
        start = nodes + start_index;

        const size_t goal_index = search_node(strtoull(argv[3], NULL, 10), nodes, n_nodes);
        if(goal_index == (size_t) -1) {
            fprintf(stderr, "Could not find goal node with id %s\n", argv[3]);
            return 4;
        }
        goal = nodes + goal_index;
    }

    const clock_t start_time = clock();
    const Bool result = astar(start, goal);
    const clock_t end_time = clock();

    if(result == FALSE) {
        fprintf(stderr, "Could not find path between %zu and %zu\n", start->id, goal->id);
        return 5;
    }

    Node *tmp = goal;
    Node *pv = goal->parent;
    Node *ppv;
    goal->parent = NULL;
    start->parent = NULL;

    while(tmp != start) {
        ppv = pv->parent;
        pv->parent = tmp;

        tmp = pv;
        pv = ppv;
    }

    printf("id,lat,lon\n");
    tmp = start;
    while(tmp != NULL) {
        print_node(tmp);
        tmp = tmp->parent;
    }

    const float elapsed_time = ((float) (end_time - start_time)) / ((float) CLOCKS_PER_SEC);
    printf("A* algorithm run in %f seconds\n", elapsed_time);
    printf("Found distance: %f meters\n", goal->distance);

    return 0;
}
