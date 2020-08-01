//  Assignment 2 Question 2:2
//  Created by Ryan Galloway on 6/16/20.
//
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 5

void *thread_work(void *thread_id)
{
    long count = 1000000;
    printf("Thread is working and detahced\n");
    for(long i = 1; i < count; i++)
    {
        printf("Spawned thread is still counting: %ld\n", i);
    }
    pthread_exit(NULL);
    
}

int main(int argc, char *argv[])
{
    pthread_t thread_id;
    
    char *message = "Thread 1";
    
    printf("Creating thread to detach\n");;
    pthread_create(&thread_id, NULL, (void*)&thread_work, (void*) message);
    
    pthread_detach(thread_id);
    printf("Main thread exiting\n");
    printf("===========================\n");
    sleep(1);
    //pthread_join(thread_id, NULL);
    exit(1);
    return 0;
}
