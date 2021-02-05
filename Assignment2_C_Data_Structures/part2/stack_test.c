// Compile this assignment with:
//
// gcc stack_test.c -o stack_test
//
// Run with:
// ./stack_test
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "mystack.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// A sample test of your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.
int unitTest1(int status){
    printf("=======Stack unitTest1=======\n");
    stack_t* test1 = create_stack(MAX_DEPTH);
    stack_enqueue(test1,1);
    print_stack(test1);
    stack_dequeue(test1);
    print_stack(test1);

    free_stack(test1);

    return 1;
}

int unitTest2(int status){
    printf("=======Stack unitTest2=======\n");
    stack_t* test2 = create_stack(MAX_DEPTH);
    stack_enqueue(test2,1);
    stack_enqueue(test2,2);
    stack_enqueue(test2,3);
    stack_enqueue(test2,4);
    stack_enqueue(test2,5);
    stack_enqueue(test2,6);
    stack_enqueue(test2,7);
    stack_enqueue(test2,8);
    stack_enqueue(test2,9);
    stack_enqueue(test2,10);
    print_stack(test2);
    free_stack(test2);

    return 1;
}

int unitTest3(int status){
    printf("========stack unitTest3========\n");
    stack_t* test3 = create_stack(32);
    int i =0;
    for(i=0; i < 32; i++){
        stack_enqueue(test3,1);
    }
    print_stack(test3);
    for(i=0; i < 32; i++){
        stack_dequeue(test3);
    }
    print_stack(test3);
    free_stack(test3);

    return 1;
}

int unitTest4(int status){
    printf("========stack unitTest4========\n");
    stack_t* test4 = create_stack(32);
    int i =0;
    for(i=0; i < 32; i++){
       stack_enqueue(test4,1);
    }
    print_stack(test4);
    for(i=0; i < 32; i++){
        stack_dequeue(test4);
    }
    print_stack(test4);
    for(i=0; i < 32; i++){
        stack_enqueue(test4,1);
    }
    print_stack(test4);
    for(i=0; i < 32; i++){
        stack_dequeue(test4);
    }
    print_stack(test4);
    free_stack(test4);

    return 1;
}

int unitTest5(int status){
    printf("=======Stack unitTest5=======\n");

    stack_t* test5 = create_stack(32);
    free_stack(test5);

    return 1;
}

int unitTest6(int status){
    printf("============Stack unitTest6========\n");
    
    stack_t* test6 = create_stack(0);
    stack_enqueue(test6, 1);
    print_stack(test6);
    free_stack(test6);
    return 1;

}

int unitTest7(int status){
    printf("========Stack unitTest7)\n");
    
    stack_t* test7 = create_stack(32);
    int i;
    for(i = 0; i < 34; i++){
        stack_enqueue(test7, i);
    }
    print_stack(test7);
    free_stack(test7);
}


// TODO: Add tests here
int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTest6,
    unitTest7,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter =0;
    while(unitTests[counter]!=NULL){
        unitTests[counter](1);
        counter++;
    }

    return 0;
}
