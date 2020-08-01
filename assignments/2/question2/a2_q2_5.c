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
    long count = 5500000;
    printf("Thread is working\n");
    printf("===========================\n");
    for(long i = 1; i < count; i++)
    {
        printf("Spawned thread is still counting: %ld\n", i);
    }
}

int main(int argc, char *argv[])
{
    pthread_t thread_id;
    
    char *message = "Thread 1";
    
    printf("Creating thread\n");;
    pthread_create(&thread_id, NULL, (void*)&thread_work, (void*) message);
    
    //detach the main thread
    pthread_detach(pthread_self());
    sleep(1);
    printf("Main thread dying=====================================\n");
    
    return 0;
}
