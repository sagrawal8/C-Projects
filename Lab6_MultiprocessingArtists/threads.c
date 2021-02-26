// gcc -lpthread threads.c -o threads

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#define NTHREADS 64
int colors[64][64*3];
int counter = 0;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

//Paint Function
void paint(int workID) {
    printf("Artist %d is painting\n",counter);
    int i;
    if(workID < 0)
    {
        workID = 0;
    }
    else if(workID > 255)
    {
        workID = 255;
    }
    for(i =0; i < 64*3; i++){
        colors[counter][i] = workID;
    }
}

void *mythread(void *vargp){
    pthread_mutex_lock(&mutex1);
        paint(counter + 19);
    pthread_mutex_unlock(&mutex1);
    counter++;
    return NULL;
}

int main(int argc, char** argv){
    pthread_t tids[NTHREADS];
    printf("Counter starts at: %d\n", counter);
    int i;
    for(i = 0; i < NTHREADS; ++i)
    {
        pthread_create(&tids[i], NULL, mythread, NULL);
    }
    
    for(i = 0; i < NTHREADS; ++i)
    {
        pthread_join(tids[i], NULL);       
    }
    printf("Final counter value: %d\n", counter);
    
    FILE *fp;
    fp = fopen("vfork.ppm","w+");
    fputs("P3\n",fp);
    fputs("64 64\n",fp);
    fputs("255\n",fp);
    int j;
    for(i =0; i < 64;i++){
        for(j =0; j < 64*3; j++){
            fprintf(fp,"%d",colors[i][j]);
            fputs(" ",fp);      
        }
        fputs("\n",fp);
    }
    fclose(fp);
    return 0;
}
