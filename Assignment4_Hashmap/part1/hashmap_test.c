// Note: This is not an exhaustive test suite, but gives you the idea
//       of some tests you might want to create.
//       Adding more tests and slowly making them more and more complicated
//       as you develop your library is recommended.
//
// Compile this assignment with: gcc -g -Wall hashmap_test.c -o hashmap_test
//
// Run with: ./hashmap_test
//
//
// Include parts of the C Standard Library
// These have been written by some other really
// smart engineers.
#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

// Our library that we have written.
// Also, by a really smart engineer!
#include "my_hashmap.h"
// Note that we are locating this file
// within the same directory, so we use quotations
// and provide the path to this file which is within
// our current directory.


// A sample collection of tests for your program
// You can add as many unit tests as you like
// We will be adding our own to test your program.


// Tests creation and deletion of the hashmap
// Ideally does not cause any segfaults, and this
// is considered passing.
int unitTest1(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(12);    
    hashmap_delete(test);
    passed = 1;
    return passed;
}

// Tests has_key for a missing key
int unitTest2(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    
    if(hashmap_hasKey(test, "cow")==0){
      passed = 1;
    }
   hashmap_printKeys(test); 
    hashmap_delete(test);
    return passed;
}


// Tests insert and has_key
int unitTest3(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    hashmap_insert(test,"bat", "A flying rat");
    hashmap_update(test, "bat", "A flying flying rat");
    hashmap_printKeys(test);
    if(hashmap_hasKey(test, "cow")==1){
      passed = 1;
    }
   
    hashmap_delete(test);
    return passed;
}

// Tests insert and has_key and remove key
int unitTest4(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    hashmap_insert(test,"bat", "A flying flying rat");
    hashmap_insert(test,"capybara", "An actual mat");
    hashmap_removeKey(test, "cow");
    hashmap_printKeys(test);
    if(hashmap_hasKey(test, "cow")==0){
      passed = 1;
    }
    
    hashmap_delete(test);

    return passed;
}

// Tests update_key
int unitTest5(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(12);
    hashmap_insert(test,"cow","A common farm animal.");
    hashmap_update(test, "cow", "A common farm animal in Ohio.");
    hashmap_printKeys(test);
    if(hashmap_hasKey(test, "cow")==1){
      passed = 1;
    }
    
    hashmap_delete(test);
    return passed;
}

int unitTest6(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(1);
    hashmap_insert(test, "cow", "A common farm animal");
    char* cowValue;
    cowValue = hashmap_getValue(test, "cow");
    if(strcmp(cowValue, "A common farm animal") == 0){
    passed = 1;
    }
    printf("%s\n", cowValue);
    hashmap_delete(test);
    return passed;
}

int unitTest7(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(1);
    hashmap_insert(test, "chicken", "A common farm animal");
    char* cowValue;
    cowValue = hashmap_getValue(test, "cow");
    if(cowValue == NULL){
    passed = 1;
    }
    printf("%s\n", cowValue);
    hashmap_delete(test);
    return passed;
}

int unitTest8(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(2);
    hashmap_insert(test, "cow", "A common farm animal");
    hashmap_insert(test, "cow", "LALALALLALA");
    hashmap_printKeys(test);
    passed = 1;
    hashmap_delete(test); 
    
    return passed;
}

int unitTest9(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(1);
    hashmap_insert(test, "cow", "A common farm animal");
    hashmap_insert(test, "ow", "LALALALLALA");
    hashmap_insert(test, "capybara", "a water animal");
    hashmap_printKeys(test);
    passed = 1;
    hashmap_delete(test);

    return passed;
}

int unitTest10(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(3);
    hashmap_insert(test, "cow", "A common farm animal");
    hashmap_insert(test, "ow", "LALALALLALA");
    hashmap_insert(test, "capybara", "a water animal");
    hashmap_printKeys(test);
    passed = 1;
    hashmap_delete(test);

    return passed;
}

int unitTest11(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(3);
    hashmap_insert(test, "cow", "A common farm animal");
    hashmap_insert(test, "ow", "LALALALLALA");
    hashmap_insert(test, "capybara", "a water animal");
    hashmap_insert(test, "bat", "flying animal");
    hashmap_insert(test, "rat", "a rodent");
    hashmap_printKeys(test);
    hashmap_removeKey(test, "rat");
    hashmap_printKeys(test);
    hashmap_removeKey(test, "capybara");
    hashmap_printKeys(test);
    hashmap_removeKey(test, "cow");
    hashmap_removeKey(test, "capybara");
    hashmap_printKeys(test);
    passed = 1;
    hashmap_delete(test);

    return passed;
}


int unitTest12(int status){
    int passed = 0;
    hashmap_t* test = hashmap_create(3);
    hashmap_insert(test, "cow", "A common farm animal");
    hashmap_insert(test, "ow", "LALALALLALA");
    hashmap_insert(test, "capybara", "a water animal");
    hashmap_insert(test, "bat", "flying animal");
    hashmap_insert(test, "rat", "a rodent");
    hashmap_printKeys(test);
    hashmap_removeKey(test, "bat");
    hashmap_printKeys(test);
    hashmap_removeKey(test, "capybara");
    hashmap_printKeys(test);
    hashmap_removeKey(test, "cow");
    hashmap_removeKey(test, "capybara");
    hashmap_printKeys(test);
    if(hashmap_hasKey(test, "ow") && hashmap_hasKey(test, "rat")){
        passed = 1;
    }
    hashmap_delete(test);

    return passed;
}



int (*unitTests[])(int)={
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTest6,
    unitTest7,
    unitTest8,
    unitTest9,
    unitTest10,
    unitTest11,
    unitTest12,
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
	printf("========unitTest %d========\n",counter);
        if(1==unitTests[counter](1)){
		printf("passed test\n");
		testsPassed++;	
	}else{
		printf("failed test, missing functionality, or incorrect test\n");
	}
        counter++;
    }

    printf("%d of %d tests passed\n",testsPassed,counter);

    return 0;
}
