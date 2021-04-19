// =================== Support Code =================
// Graph.
//
//
//
// - Implement each of the functions to create a working graph.
// - Do not change any of the function declarations
//   - (i.e. graph_t* create_graph() should not have additional arguments)
// - You should not have any 'printf' statements in your graph functions.
//   - (You may consider using these printf statements to debug, but they should be removed from your final version)
// ==================================================
#ifndef MYGRAPH_H
#define MYGRAPH_H

#include "my_dll.h"
#include <stdlib.h>
#include <assert.h>
// Create a graph data structure
typedef struct graph{
    int numNodes;
    int numEdges;
    dll_t* nodes;     //an array of nodes storing all of our nodes.
}graph_t;

typedef struct graph_node{
    int data;
    dll_t* inNeighbors;
    dll_t* outNeighbors;
}graph_node_t;

// Creates a graph
// Returns a pointer to a newly created graph.
// The graph should be initialized with data on the heap.
// The graph fields should also be initialized to default values.
// Returns NULL if we cannot allocate memory.
graph_t* create_graph(){
    // Modify the body of this function as needed.
    graph_t* myGraph= malloc(sizeof(graph_t));
    myGraph->nodes = create_dll();
    myGraph->numEdges = 0;
    myGraph->numNodes = 0;
    if(!myGraph) {
        return NULL;
    }
    return myGraph;
}

// Returns the node pointer if the node exists.
// Returns NULL if the node doesn't exist or the graph is NULL
graph_node_t* find_node( graph_t * g, int value){
    if(!g){
        return NULL;
    }
    node_t* itr = g->nodes->head;
    while(itr != NULL) {
        graph_node_t* graphNode = itr->data;
        if(graphNode->data == value){
            return graphNode;
        }
        itr = itr->next;
    }  
    
    return NULL;
}

// Creates a graph node
// Note: This relies on your dll implementation.
graph_node_t * create_graph_node(int value){
    graph_node_t * graph_node = malloc(sizeof(graph_node_t));
    
    if ( graph_node == NULL ) return NULL;
    
    graph_node->data = value;
    graph_node->inNeighbors = create_dll();
    graph_node->outNeighbors = create_dll();
    
    return graph_node;
}

// Returns 1 on success
// Returns 0 on failure ( or if the node already exists )
// Returns -1 if the graph is NULL.
int graph_add_node(graph_t* g, int value){
    if ( g == NULL ) return -1;
    
    if (find_node(g, value) != NULL) return 0;
    
    graph_node_t * newNode = create_graph_node(value);
    if ( newNode == NULL ) return -1;
    
    assert(g->nodes);
    if(dll_push_back(g->nodes, newNode)==0){return 0;}
    g->numNodes++;
    
    return 1;
}
int graph_remove_edge(graph_t * g, int source, int destination);
// Returns 1 on success
// Returns 0 on failure ( or if the node doesn't exist )
// Returns -1 if the graph is NULL.
int graph_remove_node(graph_t* g, int value){
    // The function removes the node from the graph along with any edges associated with it.
    // That is, this node would have to be removed from all the in and out neighbor's lists that countain it.
    
    if(!g) {return -1;}
    if(find_node(g, value) == NULL) {return 0;}
    node_t* itr = g->nodes->head;
    int flag = -1;
    int count = 0;
    node_t* temp;
    graph_node_t* pointerToRemove = find_node(g, value);
    while(itr != NULL){
        graph_node_t* graphNode = itr->data;
        //if node contains value
        if(graphNode->data == value){
            node_t* inItr = graphNode->inNeighbors->head;
            node_t* outItr = graphNode->outNeighbors->head;
            //remove every edge from inNeighbor List
            while(inItr != NULL){
                node_t* temp = inItr->next;
                graph_node_t* source = inItr->data;
                graph_remove_edge(g, source->data, graphNode->data);
                inItr = temp;
            }
            //remove every edge from outNeighbor list
            while(outItr != NULL){
                node_t* temp = outItr->next;
                graph_node_t* destination = outItr->data; 
                graph_remove_edge(g, graphNode->data, destination->data);
                outItr = temp;
            }    
            free_dll(graphNode->inNeighbors);
            free_dll(graphNode->outNeighbors);
            free(graphNode);
            dll_remove(g->nodes, count);
            return 1;
        }
        count++;            
    }
                               

 return 0;   
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    if(!g){return -1;} 
    if(find_node(g,source) == 0 || find_node(g,destination) == 0) {return 0;}
    graph_node_t* inNeighborNode = find_node(g, source);
    graph_node_t* outNeighborNode = find_node(g,destination);
    node_t* inItr = outNeighborNode->inNeighbors->head;
    while(inItr != NULL) {
        if(inItr->data == inNeighborNode) {return 1;}
        inItr = inItr->next;
    }
    return 0;
}
     

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge already exists )
// Returns -1 if the graph is NULL.
int graph_add_edge(graph_t * g, int source, int destination){
    // The function adds an edge from source to destination but not the other way.
    // Make sure you are not adding the same edge multiple times.
    // Make sure you modify the in and out neighbors appropriatelly. destination will be an out neighbor of source.
    // Source will be an in neighbor of destination.
    if(!g) {return -1;}
    if(find_node(g, source) == 0 || find_node(g,destination) == 0) {return 0;} 
    if(contains_edge(g, source, destination)) {return 0;}
    graph_node_t* inNeighborNode = find_node(g, source);
    graph_node_t* outNeighborNode = find_node(g, destination); 
    dll_push_back(inNeighborNode->outNeighbors, outNeighborNode);
    dll_push_back(outNeighborNode->inNeighbors, inNeighborNode);
    g->numEdges++;    
    return 1;   
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist, or the edge doesn't exists )
// Returns -1 if the graph is NULL.
int graph_remove_edge(graph_t * g, int source, int destination){
    //The function removes an edge from source to destination but not the other way.
    //Make sure you remove destination from the out neighbors of source.
    //Make sure you remove source from the in neighbors of destination.
    if(!g) {return -1;}
    if(find_node(g, source) == 0 || find_node(g,destination) == 0) {return 0;}
    if(!contains_edge(g, source, destination)) {return 0;}
    graph_node_t* outNeighborNode = find_node(g, source);
    graph_node_t* inNeighborNode = find_node(g, destination);
    node_t* inItr = inNeighborNode->inNeighbors->head;
    node_t* outItr = outNeighborNode->outNeighbors->head;
    int count = 0;
    while(inItr != NULL) {
        graph_node_t* graphNode = inItr->data;
        if(graphNode->data == source){
            dll_remove(inNeighborNode->inNeighbors, count);
        }
        count++;
        inItr = inItr->next;
    }
    count = 0;
     while(outItr != NULL) {
        graph_node_t* graphNode = outItr->data;
        if(graphNode->data == destination){
            dll_remove(outNeighborNode->outNeighbors, count);
        }
        count++;
        outItr = outItr->next;
    }
    g->numEdges--;
    return 1;
}

//Returns dll_t* of all the in neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getInNeighbors( graph_t * g, int value ){
    return find_node(g, value)->inNeighbors;
}

// Returns the number of in neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumInNeighbors( graph_t * g, int value){
    return find_node(g,value)->inNeighbors->count;   
}

// Returns dll_t* of all the out neighbors of this node.
// Returns NULL if thte node doesn't exist or if the graph is NULL.
dll_t* getOutNeighbors( graph_t * g, int value ){
    return find_node(g, value)->outNeighbors; 
}

// Returns the number of out neighbors of this node.
// Returns -1 if the graph is NULL or the node doesn't exist.
int getNumOutNeighbors( graph_t * g, int value){
     return find_node(g, value)->outNeighbors->count;  
}

// Returns the number of nodes in the graph
// Returns -1 if the graph is NULL.
int graph_num_nodes(graph_t* g){
    if(!g){return -1;}
    return g->numNodes;
}

// Returns the number of edges in the graph,
// Returns -1 on if the graph is NULL
int graph_num_edges(graph_t* g){
    if(!g){return -1;}
    return g->numEdges;
}
// Free graph
// Removes a graph and ALL of its elements from memory.
// This should be called before the program terminates.
// Make sure you free all the dll's too.
void free_graph(graph_t* g){

}

void print_graph(graph_t* g) {
    node_t* itr = g->nodes->head;
    while(itr != NULL){
        graph_node_t* each = itr->data;
        printf("Node is %d\n", each->data);
        node_t* inItr = each->inNeighbors->head;
        node_t* outItr = each->outNeighbors->head;
        while(inItr != NULL){
            graph_node_t* eachIn = inItr->data;
            printf("InNeighbor is: %d\n", eachIn->data);
            inItr = inItr->next;
        }
         while(outItr != NULL){
            graph_node_t* eachOut = outItr->data;
            printf("outNeighbor is: %d\n", eachOut->data);
            outItr = outItr->next;
        }
        printf("\n");
        itr = itr->next;
    }    
}
#endif
