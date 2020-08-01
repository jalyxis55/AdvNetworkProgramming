// jalyxis55
// Summer 2020
// Pthreads


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COUNT 5

// Work function for Q2P1
void *q2p1Worker(void *t_id)
{
	long tid = (long)t_id;
	int x = 15;
	int i = 0;

	for(i = 1; i < x; i++)
	{
		printf("Thread #%ld, Count: %d\n", tid, i);
	}

	pthread_exit(NULL);
}

// Worker function for Q2P2
void *q2p2Worker(void *t_id)
{
	long tid = (long)t_id;
	long x = 10000;
	int i = 1;
	printf("Detached thread");
	for(i = 1; i < x; i++)
	{
		printf("Thread #%ld, Count: %d\n", tid, i);
	}

	pthread_exit(NULL);
}

// Worker function for Q2P3
void *q2p3Worker(void *t_id)
{
	long tid = (long)t_id;
	int x = 15;
	int i = 1;

	for(i = 1; i < x; i++)
	{
		printf("Thread #%ld, Count: %d\n", tid, i);
		if (i = 5)
			exit(1);
	}
}

// Worker function for Q2P4
void *q2p4Worker(void *t_id)
{
	long tid = (long)t_id;
	long x = 50;
	long i = 1;
	printf("Detached thread");

	for(i = 1; i < x; i++)
	{
		printf("Thread #%ld, Count: %d\n", tid, i);
	}
	exit(1);
}

// Worker function for Q2P5
void *q2p5Worker(void *t_id)
{
	long tid = (long)t_id;
	long x = 1000000;
	long i = 1;

	for(i = 1; i < x; i++)
	{
		printf("Thread #%ld, Count: %d\n", tid, i);
	}
}

int main(int argc, char *argv[])
{
	int option;
	long i, n = 0;
	pthread_t* tHandler;
	pthread_t tid;
	char *str = "Main Thread";


	//if(argc != 2)
	//{
		//printf("Usage: ./2b <integer for question part");
		//return 0;
	//}

	// Switch statement to run which part of the question
	printf("Which question part would you like to run? (1-5)\n");
	scanf("%d", &option);

	tHandler = malloc(COUNT * sizeof(pthread_t));

	switch(option)
	{
		// Question 2 Part 1
		case 1:
			printf("=================\n");
			printf("Question 2 Part 1\n");
			printf("=================\n");

			printf("Thread creation in main()\n");
			for(i = 0; i < COUNT; i++)
			{
				pthread_create(&tHandler[i], NULL, (void*) &q2p1Worker, (void*) i);
			}

			printf("Exit\n");
			printf("=================\n");
			pthread_exit(NULL);
		// Question 2 Part 2
		case 2:
			printf("=================\n");
			printf("Question 2 Part 2\n");
			printf("=================\n");

			printf("Thread creation in main()");
			pthread_create(&tid, NULL, (void*) &q2p2Worker, (void*) str);

			pthread_detach(tid);
			printf("Exit\n");
			printf("=================\n");

			exit(1);
		// Question 2 Part 3
		case 3:
			printf("=================\n");
			printf("Question 2 Part 3\n");
			printf("=================\n");

			printf("Thread creation in main()\n");

			for(i = 0; i < COUNT; i++)
			{
				pthread_create(&tHandler[i], NULL, (void*) &q2p3Worker, (void*) i);
			}

			printf("New threads\n");
			printf("=================\n");

			for(n = 0; n < COUNT; n++)
			{
				pthread_join(tHandler[n], NULL);
			}
		case 4:
			printf("=================\n");
			printf("Question 2 Part 4\n");
			printf("=================\n");

			printf("Thread creation in main()\n");
			pthread_create(&tid, NULL, (void*) &q2p4Worker, (void*) str);

			pthread_detach(tid);

			sleep(3);

			printf("main() thread is running\n");
		case 5:
			printf("=================\n");
			printf("Question 2 Part 5\n");
			printf("=================\n");

			printf("Thread creation in main()\n");
			pthread_create(&tid, NULL, (void*) &q2p5Worker, (void*) str);

			pthread_detach(pthread_self());
			sleep(3);
			printf("main() thread dead...........\n");
		default:
			printf("Please enter question part to run: 1-5\n");
	}

	return 0; 
}