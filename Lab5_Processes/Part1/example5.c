#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    char* myargv[16];
    myargv[0] = "pwd";
    
    //myargv[1] = "-n";
     
    myargv[1]=NULL;     
    if(fork()==0){
        execvpe(myargv[0],myargv,NULL);
        printf("Child: Should never get here\n");
        exit(1);
    }
    else{
        wait(NULL);
        printf("This always prints last\n");
    }
    
    return 0;
}
