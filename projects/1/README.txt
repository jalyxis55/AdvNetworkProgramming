Jalyxis55
Summer 2020
Socket Options

-----------------------------------------------------------------------------------------
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
__________________________________________________________________________________________
For Linux

To compile:
1. Download cli.c, serv.c, and options.h
2. Upload cli.c and options.h to client machine and serv.c and options.h to server machine
3. Compile using:
	gcc -o cli cli.c
	gcc -o serv serv.c
4. To run:
	a. Open a terminal session on server machine
	b. Navigate to the directory where you compiled the C files
	c. Run: ./serv
	d. Open a terminal session to client machine
	e. Navigate to the directory where you compiled the C files
	f. Run: ./cli <IPofServerMachine>
