/* Jennifer Shelby
   CS 5341 - Advanced Network Programming
   Summer I 2020
   Assignment 1 - Client File
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
#include <netinet/tcp.h>
#include "options.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define PORT 53667
#define MAXSIZE 1024

int main(int argc, char **argv){
  int sockfd, oVal;
  socklen_t len;
  struct sockaddr_in servaddr;
  struct sock_opts *ptr;
  char buff[MAXSIZE];

  if(argc != 2){
    printf("Usage: cli <IPaddress>");
    return(0);
  }

  // Opens socket to server and fails if error occurs
  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    fprintf(stderr, "socket() failed.\n");
    exit(-1);
  }

  // Zero out memory
  bzero(&servaddr, sizeof(servaddr));

  // Initialize servaddr
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(PORT);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  // Connects to server and fails if error occurs
  if(connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0){
    fprintf(stderr, "connect() error.\n");
    exit(-1);
  }

  // Get and send socket options to the server
  for(ptr = sock_opts; ptr->opt_str != NULL; ptr++){
    // In the case that the socket option is undefined
    if(ptr->opt_val_str == NULL){
      char ustring[] = "undefined";
      write(sockfd, &ustring, strlen(ustring));
    }
    else{
      len = sizeof(val);
      // Check for valid socket option
      if(getsockopt(sockfd, ptr->opt_level, ptr->opt_name, &val, &len) == -1){
        fprintf(stderr, "getsockopt() error\n");
      }
      // If the socket option is linger struct
      else if (strcmp(ptr->opt_str, "SO_LINGER") == 0){
        struct linger tmpLinger;

        getsockopt(sockfd, ptr->opt_level, ptr->opt_name, &tmpLinger, &len);

        sprintf(buff, "%d", tmpLinger.l_onoff);
        write(sockfd, buff, MAXSIZE);
        sprintf(buff, "%d", tmpLinger.l_linger);
        write(sockfd, buff, MAXSIZE);
      }
      // If the socket option is timeval struct
      else if((strcmp(ptr->opt_str, "SO_RCVTIMEO") == 0) || (strcmp(ptr->opt_str, "SO_SNDTIMEO") == 0)){
        struct timeval tmpTV;

        getsockopt(sockfd, ptr->opt_level, ptr->opt_name, &tmpTV, &len);

        sprintf(buff, "%d", tmpTV.tv_sec);
        write(sockfd, buff, MAXSIZE);
        sprintf(buff, "%d", tmpTV.tv_usec);
        write(sockfd, buff, MAXSIZE);
      }
      // All other socket options 
      else{
        getsockopt(sockfd, ptr->opt_level, ptr->opt_name, &oVal, &len);

        sprintf(buff, "%d", oVal);

        write(sockfd, buff, sizeof(buff));
      }
    }
  }
  close(sockfd);
  exit(0);
}

// Implementation of functions in options.h
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
