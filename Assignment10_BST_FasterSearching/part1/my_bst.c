// Include our header file for our my_bst.c
#include "my_bst.h"

// Include any other libraries needed
#include <stdio.h>
#include <stdlib.h>

// Creates a BST
// Returns a pointer to a newly created BST.
// The BST should be initialized with data on the heap.
// The BST fields should also be initialized to default values(i.e. size=0).
bst_t* bst_create(){
    // Modify the body of this function as needed.
    bst_t* myBST = (bst_t*)malloc(sizeof(bst_t)); 
    myBST->size = 0;
    myBST->root = NULL;    
    return myBST;
}

// BST Empty
// Check if the BST is empty
// Returns 1 if true (The BST is completely empty)
// Returns 0 if false (the BST has at least one element)
int bst_empty(bst_t* t){
    if(t->size == 0 && t->root == NULL){
        return 1;
    }
    return 0;
}

// Adds a new node containng item to the BST
// The item is added in the correct position in the BST.
//  - If the data is less than or equal to the current node we traverse left
//  - otherwise we traverse right.
// The bst_function returns '1' upon success
//  - bst_add should increment the 'size' of our BST.
// Returns a -1 if the operation fails.
//      (i.e. the memory allocation for a new node failed).
// Your implementation should should run in O(log(n)) time.
//  - A recursive imlementation is suggested.
int bst_add(bst_t* t, int item){
    if(bst_empty(t)){
        bstnode_t* node = (bstnode_t*)malloc(sizeof(bstnode_t));
        node->data = item;
        node->leftChild = NULL;
        node->rightChild = NULL;
        if(!node) {
            return 0;
        }
        t->root = node;
        t->size++;
        return 1;
    }
    else {
        if(bst_addHelper(t->root, item) == 1) {
            t->size++;
            return 1;
        }    
    }
    return 0;
}

int bst_addHelper(bstnode_t* root, int item) {
    if(item < root->data && root->leftChild != NULL) {
        bst_addHelper(root->leftChild, item);
    }
    else if (item > root->data && root->rightChild != NULL) {
        bst_addHelper(root->rightChild, item);
    }
    else {
        bstnode_t* node = (bstnode_t*)malloc(sizeof(bstnode_t));
        node->data = item;
        node->leftChild = NULL;
        node->rightChild = NULL;
        if(!node) {
            return 0;
        }
        root = node;
        return 1;
    }
    return 0;
}

// Prints the tree in ascending order if order = 0, otherwise prints in descending order.
// For NULL tree -- print "(NULL)".
// It should run in O(n) time.
void bst_print(bst_t *t, int order){
    if(NULL == t){
        printf("(NULL)");
    }else if(bst_empty(t)){
        printf("Tree is empty");  
    }
    else {
        if(order == 0) {
            printInOrder(t->root);
        }
        else if(order == 1) {
            printPostOrder(t->root);
        }
    }      
}

void printInOrder(bstnode_t* node) {
    if(node == NULL){
        return;
    }
    printInOrder(node->leftChild);
    printf("%c\n", node->data);
    printInOrder(node->rightChild);   
}

void printPostOrder(bstnode_t* node){
    if(node == NULL){
        return;
    }
    printInOrder(node->rightChild);
    printf("%c\n", node->data);
    printInOrder(node->leftChild);
}
 
// Returns the sum of all the nodes in the bst. 
// exits the program for a NULL tree. 
// It should run in O(n) time.
int bst_sum(bst_t *t){
    if(t == NULL){
        exit(1);
    } 
    else if(bst_empty(t)){
        return 0;
    }
    else {
        int sum = 0;
        return bst_sumHelper(t->root, sum);
    }
}   

int bst_sumHelper(bstnode_t* root, int sum){
    if(root == NULL){
        return 0;
    }
    sum = sum + root->data;
    bst_sumHelper(root->leftChild, sum);
    bst_sumHelper(root->rightChild, sum);
    return sum;
}

// Returns 1 if value is found in the tree, 0 otherwise. 
// For NULL tree it exists the program. 
// It should run in O(log(n)) time.
int bst_find(bst_t * t, int value){
    if(t == NULL){
        exit(1);
    }
    else if (bst_empty(t)){
        return 0;
    }
    else {
        return bst_findHelper(t->root, value);
    } 
}

int bst_findHelper(bstnode_t* node, int value){
    if(node == NULL) {
        return 0;
    }
    else if(node->data == value) {
        return 1;
    }
    else if(value < node->data) {
        bst_findHelper(node->leftChild, value);
    }
    else {
        bst_findHelper(node->rightChild, value);
    }
    return 0;
}
// Returns the size of the BST
// A BST that is NULL exits the program.
// (i.e. A NULL BST cannot return the size)
unsigned int bst_size(bst_t* t){
    if(t->size == 0){
        exit(1);
    }
    return t->size;
}

// Free BST
// Removes a BST and ALL of its elements from memory.
// This should be called before the proram terminates.
void bst_free(bst_t* t){
    if(t == NULL) {
     return;
    }
    else if(bst_empty(t)){
        free(t->root);
        free(t);
        return;
    }
    else {
        bst_freeHelper(t->root);
        free(t);
        return;
    }
}

void bst_freeHelper(bstnode_t* node) {
    if(node == NULL) {
        return;
    }
    bst_freeHelper(node->rightChild);
    bst_freeHelper(node->leftChild);
    free(node);
}
