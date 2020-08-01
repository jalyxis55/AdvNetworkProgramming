#include	"unp.h"

void
dg_echo(int sockfd, SA *pcliaddr, socklen_t clilen)
{
	int			n, s;
	struct msghdr str;
	struct iovec inOut[1];

	//socklen_t	len;
	char		mesg[MAXLINE];

	memset(mesg, 0, sizeof(mesg));
	memset(inOut, 0, sizeof(inOut));
	memset(&str, 0, sizeof(str));

	inOut[0].iov_base = mesg;
	inOut[0].iov_len = sizeof(mesg);

	str.msg_name = pcliaddr;
	str.msg_namelen = clilen;
	str.msg_iov = inOut;
	str.msg_iovlen = 1;

	for ( ; ; ) {
		//len = clilen;
		inOut[0].iov_len = MAXLINE;
		printf("inOut: %d\n", inOut[0].iov_len);
		n = recvmsg(sockfd, &str, 0);
		printf("n: %d, Error: %d\n", n, errno);
		//n = Recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
		s = sendmsg(sockfd, &str, 0);
		printf("s: %d, Error: %d\n", s, errno);
		//Sendto(sockfd, mesg, n, 0, pcliaddr, len);
	}
}
