/* jalyxis55
   Summer 2020
   Client File
*/

/* -------------------------------------------------------------------------------------
   Short program that will disable Nagle's algorithm. Does not to use the fgets and 
   fputs functions as they belong to the C standard library and buffer input and output).
   ------------------------------------------------------------------------------------- */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define PORT 53667
#define MAXSIZE 256

int main(int argc, char **argv)
{
	int sockfd;
	int count = 0;
	socklen_t len;
	struct sockaddr_in servaddr;
	char sBuffer[MAXSIZE];
	char rBuffer[MAXSIZE];
	clock_t start, end;
	double totalTime;

	if(argc != 2)
	{
		printf("Usage: cli <IPaddress>");
		return(0);
	}

	// Open socket to server if fails, error displays and program exits gracefully
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("socket() failed.\n");
		exit(-1);
	}

	// Set socket option to disable Nagle's algorithm (enable TCP_NODELAY)
	int x = 1;
	setsockopt(sockfd, SOL_TCP, TCP_NODELAY, (void *) &x, sizeof(x));

	// Zero out memory
	bzero(&servaddr, sizeof(servaddr));

	// Initialize servaddr
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	// Connect to server if fails, error displays and program exits gracefully
	if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
	{
		printf("connect() failed.\n");
		exit(-1);
	}

	// Send test packets to server
	//start = clock();
	for(count = 0; count < 10000; count++)
	{
		bzero(sBuffer, 256);
		bzero(rBuffer, 256);
		
		sprintf(sBuffer, "Packet %d\n", count);
		write(sockfd, sBuffer, sizeof(sBuffer));
		printf("To Server: %s", sBuffer);

		read(sockfd, rBuffer, sizeof(rBuffer));
		printf("From Server: %s", rBuffer);
	}

	printf("DONE\n");

	return(0);
}
