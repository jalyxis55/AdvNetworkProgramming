//
//  pthreads_a2.c
//  
//
//  Created by Ryan Galloway on 6/16/20.
//

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
    }
    pthread_exit(NULL);
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
    printf("Exiting main thread\n");
    printf("===========================\n");
    pthread_exit(NULL);
    
    return 0;
}
