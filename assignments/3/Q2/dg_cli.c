#include	"unp.h"

void
dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen)
{
	int	n, s;
	char 	buff[MAXLINE+1];
	//char	sendline[MAXLINE], recvline[MAXLINE + 1];
	struct msghdr str;
	struct iovec  inOut[1];

	memset(buff, 0, sizeof(buff));
	memset(inOut, 0, sizeof(inOut));
	memset(&str, 0, sizeof(str));

	inOut[0].iov_base = buff;
	inOut[0].iov_len = sizeof(buff);

	str.msg_name = pservaddr;
	str.msg_namelen = servlen;
	str.msg_iov = inOut;
	str.msg_iovlen = 1;
	str.msg_control = 0;
	str.msg_controllen = 0; 

	while (Fgets(buff, MAXLINE, fp) != NULL) {
		inOut[0].iov_len = strlen(buff) + 1;
		printf("inOut: %d\n", inOut[0].iov_len);
		s = sendmsg(sockfd, &str, 0);
		//Sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
		printf("s: %d, Error: %d\n", s, errno);
		inOut[0].iov_len = MAXLINE;
		printf("inOut: %d\n", inOut[0].iov_len);
		n = recvmsg(sockfd, &str, 0);
		printf("n: %d, Error: %d\n", n, errno);
		//n = Recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);

		buff[n] = 0;	/* null terminate */
		Fputs(buff, stdout);
	}
}
