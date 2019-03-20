#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char *argv[])
{
	struct hostent *h;
	char hostName[256];
	if (argc != 2) {
		printf("enter host name : \n");
		scanf("%s",hostName);
		h = gethostbyname(hostName);
		
	}else{
		h = gethostbyname(argv[1]);
	}

	
	/*connect to server*/ 
	struct sockaddr_in saddr;
	int sockfd;
	unsigned short port = 8784;
	if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Error creating socket\n");
	}
	if (h == NULL) {
		fprintf(stderr,"gethostbyname() failed\n");
		exit(1);
	} else {
		printf("%s = ", h->h_name);
		unsigned int i=0;
		while ( h -> h_addr_list[i] != NULL) {
			printf( "%s ", inet_ntoa( *( struct in_addr*)( h -> h_addr_list[i])));
			i++;
		}
		printf("\n");
		exit(0);
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length); saddr.sin_port = htons(port);
	if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) 
	{
		printf("Cannot connect\n");
	}

}