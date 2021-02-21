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
        printf("First child Process Terminated\n");
        myargv[0] = "/bin/ls";
        myargv[1] = "-laF";
        myargv[2] = NULL;
        if(fork() == 0) {
            execve(myargv[0],myargv,NULL);
            printf("Child: Should never get here\n");
            exit(1);
        }
        else{
            wait(NULL);
            printf("Second child Process Terminated\n");
            myargv[0] = "/bin/pwd";
            myargv[1] = NULL;
            if(fork() == 0) {
                execve(myargv[0],myargv,NULL);
                printf("Child: Should never get here\n");
                exit(1);
            }
            else{
                wait(NULL);
                printf("Third child Process Terminated\n");
            }
        }
    }
return 0;
}

