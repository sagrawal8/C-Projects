//used zentut after i was done coding to see if it did it right


#include <stdio.h>
#include <stdlib.h> // contains the functions free/malloc
#include <stdbool.h>
typedef struct node{
    int wins;
    int year;
    struct node* next;
}node_t;


// Write your functions here
// There should be 1.) create_list 2.) print_list 3.) free_list

// You may create as many helper functions as you like.

node_t* create_list(){
    int data[200];
    int wins[200];
    int year[200];
    FILE *fptr;
    int c;        //holds index position for data array
    int count;    //counts number of redsox data entries * 2
    if((fptr = fopen("redSoxData.txt", "r")) == NULL){
        printf("error opening file!\n");
    }
    c = 0;
    while(!feof(fptr)){
        fscanf(fptr, "%d", &data[c]);
        c++;
    }
    count = c;
   
    int i;
    i = 0;
    int sizeOfData;
    sizeOfData = *(&data + 1) - data;    //copy years from data array to year array
    for(c = 0; c < count; c = c + 2){
        year[i] = data[c];
        i++;
    }   
    i = 0;
    for(c = 1; c < count; c = c + 2){   //copy wins from data array to win array
        wins[i] = data[c];
        i++;   
    }
   
    node_t* head = NULL;
    for(i = 0; i < count/2; i ++){          
        node_t* new_node = (node_t*)malloc(sizeof(node_t));
        new_node->wins = wins[i];
        new_node->year = year[i];    
        if(head == NULL){
            new_node->next = NULL;
            head = new_node;
        }
        else{
        new_node->next = head;
        head = new_node;
        }
    }
   return head;
}


void free_list(node_t* head ){
    node_t* iterator, *temp_ptr;
    if(head != NULL)
        {
            iterator = head->next;
            head->next = NULL;
            while(iterator->next != NULL){
                temp_ptr = iterator->next;
                free(iterator);
                iterator = temp_ptr;
            }
    }
}

void print_list(node_t* head){
    node_t* iterator;
    iterator = head;
    if(head != NULL)
    {
        while(iterator->next != NULL){
             printf("Wins for year %d are %d.\n", iterator->year, iterator->wins);
            iterator = iterator->next;
        }
    }
}   

int main (){

node_t* iterator;
iterator = create_list();
print_list(iterator);
return 0;  
 
}


