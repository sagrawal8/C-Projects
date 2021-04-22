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
    int visited;
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
    graph_node->visited = 0;
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
        itr = itr->next;
        count++;            
    }
                               

    return 0;   
}

// Returns 1 on success
// Returns 0 on failure ( or if the source or destination nodes don't exist )
// Returns -1 if the graph is NULL.
int contains_edge( graph_t * g, int source, int destination){
    if(!g){return -1;} 
    if(find_node(g,source) == NULL || find_node(g,destination) == NULL) {return 0;}
    
    //find both source and dest nodes and check whether source node lies in dest node's outneighbor list.
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
    if(find_node(g, source) == NULL || find_node(g,destination) == NULL) {return 0;} 
    if(contains_edge(g, source, destination)) {return 0;}
    
    //Find source and dest nodes and add in each other inNeighbor/outNeighbor lists.
    graph_node_t* inNeighborNode = find_node(g, source);
    graph_node_t* outNeighborNode = find_node(g, destination); 
    dll_push_back(inNeighborNode->outNeighbors, outNeighborNode);  //add a reference of dest node to outNeighbor list.
    dll_push_back(outNeighborNode->inNeighbors, inNeighborNode);   //add a reference of source node to inNeighbor list.
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
    if(find_node(g, source) == NULL || find_node(g,destination) == NULL) {return 0;}
    if(!contains_edge(g, source, destination)) {return 0;}
    
    //Find source and dest nodes.
    graph_node_t* outNeighborNode = find_node(g, source);
    graph_node_t* inNeighborNode = find_node(g, destination);
    node_t* inItr = inNeighborNode->inNeighbors->head;
    node_t* outItr = outNeighborNode->outNeighbors->head;
    int count = 0;
    //remove source node from dest node's inNeighbor list.
    while(inItr != NULL) {
        graph_node_t* graphNode = inItr->data;
        if(graphNode->data == source){
            dll_remove(inNeighborNode->inNeighbors, count);
        }
        count++;
        inItr = inItr->next;
    }
    //remove dest node from sources outneighbor list.
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
    node_t* itr = g->nodes->head;
    while(itr != NULL) {
        node_t* temp = itr->next;
        graph_node_t* each = itr->data;
        free_dll(each->inNeighbors);
        free_dll(each->outNeighbors);
        free(each);
        free(itr);
        itr = temp;
    }
    free(g->nodes);
    free(g);
}

// Custom method to print graph.
// Prints each node and its in/out neighbor lists.
void print_graph(graph_t * g){
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

//returns 1 if we can reach the destination from source
// returns 0 if it is not reachable
// returns -1 if the graph is NULL (using BFS)
int is_reachable(graph_t * g, int source, int dest){
    if(!g) {return -1;}  //check if graph is null.
    if(find_node(g,source) == NULL){  //check if source node exists.
        return 0;
    }
    if(find_node(g,dest) == NULL){  //check if dest node exists.
        return 0;
    }
    graph_node_t* sourceNode = find_node(g, source);
    sourceNode->visited = 1;  //set source to visited.
    int flag = -1; //used to either start iterator from head or from head->next
    int flag2 = -1;
    //For some reason I had seg fault if this condition wasn't 
    //present even though its checked in while loop.
    if(sourceNode->outNeighbors->head == NULL){ 
        return 0;
    }
    //create dll to store outNeighbor nodes while performing BFS.
    dll_t* list = create_dll();
    node_t* outItr = sourceNode->outNeighbors->head;
    node_t* listItr = NULL;
    //listItr will be NULL on first run, therefore flag1 is used.
    while(listItr != NULL || flag == -1){
        while(outItr != NULL){ 
            graph_node_t* each = outItr->data;         
            if(each->visited == 1){      //continue if visited previously.
                outItr = outItr->next;
                continue;
            }
            if(each->data == dest){   //if dest node is reached
                free_dll(list);
                node_t* itr = g->nodes->head;
                while(itr != NULL){    //reset visited to 0.
                    graph_node_t* temp = itr->data;
                    temp->visited = 0;
                    itr = itr->next;
                }
                return 1;
            }
            each->visited = 1;
            dll_push_back(list, each);  //add outNeighbor node to list to search again.
            outItr = outItr->next;                      
        }
        if(flag2 == -1){
            listItr = list->head;
            flag2 = 0;
        }
        else{
           if(listItr->next == NULL){
                break;
            }
            listItr = listItr->next;
        }
        graph_node_t* temp = listItr->data;
        outItr = temp->outNeighbors->head;
        flag = 0;
    }   
    free_dll(list);
    node_t* itr = g->nodes->head;     //reset visited to 0 if loop ends.
    while(itr != NULL){
        graph_node_t* temp = itr->data;
        temp->visited = 0;
        itr = itr->next;
    }
    return 0;
}

//returns 1 if there is a cycle in the graph
// returns 0 if no cycles exist in the graph
// returns -1 if the graph is NULL 
// You may use either BFS or DFS to complete this task.
int has_cycle(graph_t * g){
   if(!g) {return -1;}
    if(g->numNodes == 0) {
        return 0;
    }
    node_t* graphItr = g->nodes->head;  //start from head of graph.
    while(graphItr != NULL){
        int flag = -1;
        int flag2 = -1;
        graph_node_t* headGraphNode = graphItr->data;
        headGraphNode->visited = 1;  //set visited to 1.
        dll_t* list = create_dll();
        if(headGraphNode->outNeighbors->head == NULL){ //had seg fault if condition wasnt present.
            graphItr = graphItr->next;  //if node has no outneighbors, check next node.
            free(list);
            continue;
        }  
        node_t* outItr = headGraphNode->outNeighbors->head;
        node_t* listItr = NULL;
        while(listItr != NULL || flag == -1){  //list iterator null at first run, therefore used flag.
            while(outItr != NULL){
                graph_node_t* each = outItr->data;
                if(each->visited == 1){            //check if visited node is encountered
                    free_dll(list);
                    node_t* itr = g->nodes->head;
                    while(itr != NULL){     //reset visited to 0.
                        graph_node_t* temp = itr->data;
                        temp->visited = 0;
                        itr = itr->next;
                    }
                    return 1;
                }
                each->visited = 1;
                dll_push_back(list, each);  //add outneighbor node to list for further runs.
                outItr = outItr->next;
            } 
            if(flag2 == -1){
                listItr = list->head;
                flag2 = 0;
            }
            else{
                if(listItr->next == NULL){
                    break;
                }
                listItr = listItr->next;
            }
            graph_node_t* temp = listItr->data;
            outItr = temp->outNeighbors->head;
            flag = 0;
        }
        graphItr = graphItr->next;
        free_dll(list);
    }
    node_t* itr = g->nodes->head;   //reset visited to 0.
    while(itr != NULL){
        graph_node_t* temp = itr->data;
        temp->visited = 0;
        itr = itr->next;
    }
    return 0;
}
     

// prints any path from source to destination if there 
// exists a path from the source to the destination.
// Returns 1 if there is a path from source to destination
// Returns 0 if there is not a path from a source to destination
// Returns -1 if the graph is NULL
int print_path(graph_t * g, int source, int dest){
    if(!g){return -1;}  
    if(is_reachable(g, source, dest) == 0){return 0;}  
    int flag = -1;
    node_t* temp;
    if(find_node(g,source) == NULL) {  //check if source exists.
        return 0;
    }
    graph_node_t* node = find_node(g, source);  
    if(node->outNeighbors->head == NULL){
        return 0;
    }
    dll_t* list = create_dll(); //create a list to store path
    node_t* outItr = node->outNeighbors->head; //start iteration from outneighbor list of source node.
    while(outItr != NULL){
        graph_node_t* each = outItr->data;
        if(each->data == dest){  //if destination reached, print path and free list.
            int count = 0;
            printf("%d ", source);
            while(count < dll_size(list)){
                graph_node_t* eachh = dll_get(list, count);
                printf("%d ",eachh->data);
                count++;
                }
            printf("%d\n", dest);
            free_dll(list);
            node_t* itr = g->nodes->head;
            while(itr != NULL){    //reset visited to 0.
                graph_node_t* temp = itr->data;
                temp->visited = 0;
                itr = itr->next;
            }
            return 1;
        }
        else if(is_reachable(g, each->data, dest) == 1 && each->visited == 0){ 
            //if dest is reachable from current node, add current to list.
            //and make iterator read outNeighbors of current node.
            //Doesnt give shortest path, but gives a path.
            each->visited = 1;
            dll_push_back(list, each);
            if(flag == -1){
                temp = list->head;
                graph_node_t* temp2 = temp->data;
                outItr = temp2->outNeighbors->head;
                flag = 0;    
            }
            else{
                temp = temp->next;
                graph_node_t* temp2 = temp->data;
                outItr = temp2->outNeighbors->head;
            }            
        }
        //if node is not reachable from current node, check other out neighbor nodes.
        else{
            each->visited = 1;
            outItr = outItr->next;
        }
    }
     node_t* itr = g->nodes->head;
     while(itr != NULL){    //reset visited to 0.
        graph_node_t* temp = itr->data;
        temp->visited = 0;
        itr = itr->next;
    }
    return 1;
}
#endif
