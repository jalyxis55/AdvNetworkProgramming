/* jalyxis55
   Summer 2020
   Server File
*/

/* -------------------------------------------------------------------------------------
   Short program that will disable Nagle's algorithm. Does not to use the fgets and 
   fputs functions as they belong to the C standard library and buffer input and output).
   ------------------------------------------------------------------------------------- */

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 53667
#define LISTENQ 10
#define MAXSIZE 256
#define DELAY 3

int main(int argc, char **argv)
{
   int listenfd, connfd;
   socklen_t clilen;
   struct sockaddr_in cliaddr, servaddr;
   char buffer[MAXSIZE];

   // Build socket if fails, displays error and exits gracefully
   if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
   {
      printf("socket() failed.\n");
      exit(-1);
   }

   // Zero out memory
   bzero(&servaddr, sizeof(servaddr));

   // Initialize servaddr
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port = htons(PORT);

   // Bind. If fails, display error message and exits gracefully
   if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
   {
      printf("bind() failed.\n");
      exit(-1);
   }

   // Listen
   listen(listenfd, LISTENQ);

   // Accept and read from client
   for( ; ; )
   {
      clilen = sizeof(cliaddr);
      if((connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0)
      {
         printf("accept() failed.\n");
         exit(-1);
      }

      bzero(buffer, 256);
      read(connfd, buffer, MAXSIZE);
      printf("From Client: %s", buffer);
      write(connfd, buffer, sizeof(buffer));
      printf("Echo: %s", buffer);
   }

   return 0; 
}
