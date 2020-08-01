/* Jennifer Shelby
   CS 5341 - Advanced Network Programming
   Summer I 2020
   Assignment 1 - Server File
 */

 /* ---------------------------------------------------------------
    Combine the TCP client-server example in Chapter 5 and the 
    checkopts program as follows:

        1. The client makes a TCP connection to the server
        2. The client gets each socket option value, including
           undefined option, send the value to the server. The
           server prints out the value received.
        3. For each value received by the server, the server sets
           socket options as follows:
              a. For binary option, it sets it with an opposite
                 value. That means, for example, for option
                 SO_ERROR, if the client option value is 0 
                 (disabled), then the server will set it as 1
                 (enabled).
              b. For other non-binary integer options, the server
                 will set its options value different from the 
                 received. For example, for the option SO_RCVBUF, 
                 if the received option value is 16, 124, the 
                 server may set it as 32, 248.
              c. For other options, your program can decide on
                 your own what value the server will set the value
                 for each of those options.
        4. At the end of program, server will print out all of its
           option values, just like the checkopts program.
        5. Please make sure that the client/server programs can run
           on different computers.
    --------------------------------------------------------------- */

#include <arpa/inet.h>
#include <netinet/in.h>
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 53667
#define LISTENQ 10
#define MAXSIZE 1024

int main(int argc, char **argv){
	int listenfd, connfd, len, optVal, newVal;
	socklen_t clilen;
	struct sockaddr_in cliaddr, servaddr;
	struct sock_opts *ptr;
	char buff[MAXSIZE];

	// Build Socket
	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		fprintf(stderr, "socket() failed.\n");
		exit(-1);
	}

	// Zero out memory
	bzero(&servaddr, sizeof(servaddr));
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Bind
	if(bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) <0){
		fprintf(stderr, "bind() failed.\n");
		exit(-1);
	}

	// Listen
	listen(listenfd, LISTENQ);

	for( ; ; ){
		clilen = sizeof(cliaddr);

		// Accept 
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);

		// Error checking for the accept function
		if(connfd < 0){
			fprintf(stderr, "accept() failed.\n");
			exit(-1);
		}

		// Print values sent from the client 
		printf("Client Values:\n");
		printf("==============\n");

		for(ptr = sock_opts; ptr->opt_str != NULL; ptr++){
			// If socket option passed is a linger struct
			if(strcmp(ptr->opt_str, "SO_LINGER") == 0){
				struct linger tmpLinger;
				read(connfd, buff, MAXSIZE);
				int tmpOnOff = atoi(buff);
				read(connfd, buff, MAXSIZE);
				int tmpLVal = atoi(buff);

				printf("%s: l_onoff = %d, l_linger = %d\n", ptr->opt_str, tmpOnOff, tmpLVal);

				if(tmpOnOff == 0){
					tmpLinger.l_onoff = 1;
				}
				else{
					tmpLinger.l_onoff = 0;
				}

				tmpLinger.l_linger = (tmpLVal + 15) * 2;
				len = sizeof(tmpLinger);

				setsockopt(connfd, ptr->opt_level, ptr->opt_name, &tmpLinger, len);
			}
			// If socket option passed is a timeval struct
			else if((strcmp(ptr->opt_str, "SO_RCVTIMEO") == 0) || (strcmp(ptr->opt_str, "SO_SNDTIMEO") == 0)){
				struct timeval tmpTV;
				read(connfd, buff, MAXSIZE);
				int s = atoi(buff);
				read(connfd, buff, MAXSIZE);
				int us = atoi(buff);
				printf("%s: tv_sec = %d, tv_usec = %d\n", ptr->opt_str, s, us);
				// change value
				tmpTV.tv_sec = (s + 10) * 2;
				tmpTV.tv_usec = (us + 10) * 2;

				len = sizeof(tmpTV);

				setsockopt(connfd, ptr->opt_level, ptr->opt_name, &tmpTV, len);
			}
			// All other socket options
			else{
				read(connfd, buff, MAXSIZE);
				optVal = atoi(buff);
				printf("%s: %d\n", ptr->opt_str, optVal);

				if(optVal == 0){
					newVal = 1;
				}
				else if(optVal == 1){
					newVal = 0; 
				}
				else{
					newVal = optVal * optVal;
				}
				len = sizeof(newVal);
				setsockopt(connfd, ptr->opt_level, ptr->opt_name, &newVal, len);
			}
		}
		// Print new socket options
		printf("\nNew Values:\n");
		printf("===========\n");
		for(ptr = sock_opts; ptr->opt_str != NULL; ptr++){
			printf("%s: ", ptr->opt_str);

			if(ptr->opt_val_str == NULL)
				printf("(Undefined)\n");
			len = sizeof(val);
			if(getsockopt(connfd, ptr->opt_level, ptr->opt_name, &val, &len) == -1){
				printf("getsockopt() error.\n");
			}
			else{
				printf("%s\n", (*ptr->opt_val_str)(&val, len));
			}
		}
	
	}
}



//Implementation of functions in options.h
static char    strres[128];

static char    *sock_str_flag(union val *ptr, int len){
   if (len != sizeof(int))
       snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
   else
       snprintf(strres, sizeof(strres),
                "%s", (ptr->i_val == 0) ? "off" : "on");
   return(strres);
}

static char *sock_str_int(union val *ptr, int len){
   if (len != sizeof(int))
       snprintf(strres, sizeof(strres), "size (%d) not sizeof(int)", len);
   else
       snprintf(strres, sizeof(strres), "%d", ptr->i_val);
   return(strres);
}

static char    *sock_str_linger(union val *ptr, int len){
   struct linger    *lptr = &ptr->linger_val;

   if (len != sizeof(struct linger))
       snprintf(strres, sizeof(strres),
                "size (%d) not sizeof(struct linger)", len);
   else
       snprintf(strres, sizeof(strres), "l_onoff = %d, l_linger = %d",
                lptr->l_onoff, lptr->l_linger);
   return(strres);
}

static char    *sock_str_timeval(union val *ptr, int len){
   struct timeval    *tvptr = &ptr->timeval_val;

   if (len != sizeof(struct timeval))
       snprintf(strres, sizeof(strres),
                "size (%d) not sizeof(struct timeval)", len);
   else
       snprintf(strres, sizeof(strres), "%d sec, %d usec",
                tvptr->tv_sec, tvptr->tv_usec);
   return(strres);
}
