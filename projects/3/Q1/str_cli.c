#include	"unp.h"

void
str_cli(FILE *fp, int sockfd)
{
	//char	sendline[MAXLINE], recvline[MAXLINE];
	ssize_t sm, rm;
	char strBuffer[MAXLINE];
	struct msghdr str;
	struct iovec inOut[1];
	struct cmsghdr cStr;

	memset(&strBuffer, 0, sizeof(strBuffer));
	memset(inOut, 0, sizeof(inOut));
	memset(&str, 0, sizeof(str));

	inOut[0].iov_base = strBuffer;
	inOut[0].iov_len = sizeof(strBuffer);

	str.msg_iov = inOut;
	str.msg_iovlen = 1;

	while (Fgets(strBuffer, MAXLINE, fp) != NULL) {
		inOut[0].iov_len = strlen(strBuffer) + 1;
		printf("inOut: %d\n", inOut[0].iov_len);
		sm = sendmsg(sockfd, &str, 0);
		if(sm <= 0){
			err_quit("Failed to send\n");
			printf("SM: %d, Error: %d\n", sm, errno);
		}

		rm = recvmsg(sockfd, &str, MSG_WAITALL);
		if(rm <= 0){
			printf("RM: %d, Error: %d", rm , errno);
			err_quit("Failed to receive\n");
		}

		//Writen(sockfd, sendline, strlen(sendline));

		//if (Readline(sockfd, recvline, MAXLINE) == 0)
		//	err_quit("str_cli: server terminated prematurely");

		Fputs(strBuffer, stdout);
	}
}

