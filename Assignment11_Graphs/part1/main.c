// Compile this assignment with: gcc main.c -o main
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_graph.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.

int main(int argc, const char * argv[]) {
    graph_t * graph = create_graph();
    graph_add_node(graph, 1);
    printf("here %d\n", print_path(graph, 1, 53));
    printf("here %d\n", has_cycle(graph));
    printf("here %d \n", is_reachable(graph, 1, 53));
    //printf("cycle is %d\n", print_path(graph, 5, 7));
    graph_add_node(graph, 1);
    graph_add_node(graph, 2);
    graph_add_node(graph, 3);
    graph_add_node(graph, 4);
    graph_add_node(graph, 5);
    graph_add_node(graph,6);
    graph_add_node(graph,7);
    //graph_add_edge(graph,1,7);
    graph_add_edge(graph,1,2);
    graph_add_edge(graph,2,4);
    graph_add_edge(graph,2,3);
    graph_add_edge(graph,3,5);
    graph_add_edge(graph,3,6);
    graph_add_edge(graph,6,7);
    graph_add_node(graph, 9);
    graph_add_edge(graph,7,1);
    //graph_add_edge(graph, 9, 9);
    print_graph(graph);
    //printf("%d \n", is_reachable(graph, 4, 3));
    printf("Path is %d\n", print_path(graph, 5,7));
    free_graph(graph);
    return 0;
}
