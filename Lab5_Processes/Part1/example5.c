#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    char* myargv[16];
    myargv[0] = "/bin/cat";
    myargv[1] = "-n";
    myargv[2]="example5.c"; 
    myargv[3]=NULL;     
    if(fork()==0){
        execve(myargv[0],myargv,NULL);
        printf("Child: Should never get here\n");
        exit(1);
    }
    else{
        wait(NULL);
        printf("This always prints last\n");
    }
    
    return 0;
}
