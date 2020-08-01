#include	"unp.h"

void
str_echo(int sockfd)
{
	ssize_t		n;
	char		buf[MAXLINE];
	int sm;
	struct msghdr str;
	struct iovec inOut[1];

	memset(&buf, 0, sizeof(buf));
	memset(inOut, 0, sizeof(inOut));
	memset(&str, 0, sizeof(str));

	inOut[0].iov_base = buf;
	inOut[0].iov_len = sizeof(buf);

	str.msg_iov = inOut;
	str.msg_iovlen = 1;

again:
	while ( (n = recvmsg(sockfd, &str, 0)) > 0){
		//Writen(sockfd, buf, n);
		printf ("n: %d\n", n);
		inOut[0].iov_len = strlen(buf) + 1;
		printf ("inOut: %d\n", inOut[0].iov_len);
		sm = sendmsg(sockfd, &str, 0);
		printf("sm: %d\n", sm);
	}

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}
