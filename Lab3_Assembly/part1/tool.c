// Implement your cycle count tool here.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//int
//int create_assembly_array(char* fileName){
int main (int argc, char* argv[]){ 
    FILE *fptr;
    char xyz[100];
    if((fptr = fopen(argv[1],"r")) == NULL){
        printf("error opening file.");
        exit(1);
    }
    int add_counter;
    add_counter = 0;
    int sub_counter;
    sub_counter = 0;
    int mul_counter;
    mul_counter = 0;
    int div_counter;
    div_counter = 0;
    int mov_counter;
    mov_counter = 0;
    int lea_counter;
    lea_counter = 0;
    int push_counter;
    push_counter = 0;
    int pop_counter;
    pop_counter = 0;
    int ret_counter;
    ret_counter = 0;
    while(fscanf(fptr, "%s", xyz)!= EOF){
        if(strcasestr(xyz, "#")){
            fscanf(fptr, "%[^\n]s", xyz);   
        }
        else if(strcasestr(xyz, "add")){
            add_counter++;
        }
        else if(strcasestr(xyz, "sub")){
            sub_counter++;
        }
        else if(strcasestr(xyz, "mul")){
            mul_counter++;
        }
        else if(strcasestr(xyz, "div")){
            div_counter++;
        }
        else if(strcasestr(xyz, "mov")){
            mov_counter++;
        }
        else if(strcasestr(xyz, "lea")){
            lea_counter++;
        }
        else if(strcasestr(xyz, "push")){
            push_counter++;
        }
        else if(strcasestr(xyz, "pop")){
            pop_counter++;
        }
        else if(strcasestr(xyz, "ret")){
            ret_counter++;
        }
    }
    fclose(fptr); 
    int total_instructions;
    total_instructions = add_counter + sub_counter + mul_counter + div_counter + mov_counter + lea_counter + push_counter + pop_counter + ret_counter;
    int total_cycles;
    total_cycles = add_counter + sub_counter + mul_counter * 2 + div_counter * 4 + mov_counter + lea_counter + push_counter + pop_counter + ret_counter; 
    printf("Add: %d\n", add_counter);
    printf("Sub: %d\n", sub_counter);
    printf("Mul: %d\n", mul_counter);
    printf("Div: %d\n", div_counter);
    printf("Mov: %d\n", mov_counter);
    printf("Lea: %d\n", lea_counter);
    printf("Push: %d\n", push_counter);
    printf("Pop: %d\n", pop_counter);
    printf("Ret: %d\n", ret_counter);   
    printf("Total Instructions are: %d\nTotal Cycles are: %d\n", total_instructions, total_cycles);
    return 1;
}
 
