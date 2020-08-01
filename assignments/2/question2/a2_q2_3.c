//  Assignment 2 Question 2:3
//  Created by Ryan Galloway on 6/16/20.
//
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#define NUM_THREADS 5

void *thread_work(void *thread_id)
{
    long t_id = (long)thread_id;
    int count = 11;
    
    for(int i = 1; i < count; i++)
    {
        printf("Spawned thread %ld is still counting: %d\n", t_id, i);
        if(i==3)
            exit(1);
    }
    
    
}

int main(int argc, char *argv[])
{
    pthread_t* thread_handles;
    
    thread_handles = malloc(NUM_THREADS*sizeof(pthread_t));
    printf("Main thread starting thread creation\n");;
    for(long thread = 0; thread < NUM_THREADS; thread++)
    {
        pthread_create(&thread_handles[thread], NULL, (void*)&thread_work, (void *)thread);
    }
    printf("Threads Spawned\n");
    printf("===========================\n");
    for(long j = 0; j < NUM_THREADS; j++)
    {
	    pthread_join(thread_handles[j], NULL);
    }
    return 0;
}
