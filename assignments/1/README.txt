Jennifer Shelby
CS 5341 - Advanced Network Programming
Summer I 2020
Assignment 1 - Socket Options

-----------------------------------------------------------------------------------------
Combinee the TCP client-server example in Chapter 5 and the checkopts program as follows:
	1. The client makes a TCP connection to the server.
	2. The client gets each socket option value, including undefined option, send the
	   value to the server. The server prints out the value received.
	3. For each value received by the server, the server sets socket options as 
	   follows:
		a. For binary option, it sets it with the opposite value. That means, for
		   example, for option SO_ERROR, if the client option value is 0 (disabled),
		   then the server will set it as 1 (enabled).
		b. For other non-binary integer options, the server will set its options
		   value different from the received. For example, the option SO_RCVBUFF,
		   if the received option value is 16, 124, the server may set it as 32,
		   248.
		c. For other options, your program can decide on your own what value the 
		   server will set the value for each of those options.
	4. At the end of the program, server will print out all of its option values, just
	   like the checkopts program.
	5. Please make sure that the client-server programs can run on different computers
__________________________________________________________________________________________

I worked with Ryan Galloway on this assignment to sound board logic and how the client and
server would work together. Specifically, sending the socket options from the client to the
server. 

To compile:
1. Unzip JenniferShelby_Assign1.zip
2. Upload JenniferShelby_Assign1_Cli.c, JenniferShelby_Assign1_Serv.c, and options.h
   to eros.cs.txstate.edu or zeus.cs.txstate.edu
3. Compile using:
	gcc -o cli JenniferShelby_Assign1_Cli.c
	gcc -o serv JenniferShelby_Assign1_Serv.c
4. To run:
	a. Open a terminal session on eros.cs.txstate.edu
	b. Navigate to the directory where you compiled the C files
	c. Run: ./serv
	d. Open a terminal session to zeus.cs.txstate.edu
	e. Navigate to the directory where you compiled the C files
	f. Run: ./cli 147.26.231.153
