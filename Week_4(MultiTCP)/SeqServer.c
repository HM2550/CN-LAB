//Sequential Server 

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netinet/ip.h> 
#include<netdb.h>
#include<arpa/inet.h>

int main(void)
{
	int sockfd, clientfd, client_size;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Socket creation failed!\n");
		return -1;
	}
	printf("Socket created successfully!\n");

	struct sockaddr_in servaddr, cliaddr;

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(2000);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Bind to the set port and IP:
	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
	{
		printf("Bind failed!\n");
		return -1;
	}
	printf("Bind successful!\n");

	listen(sockfd, 5);
	
	int size = sizeof(struct sockaddr);
	char send1[20], recv1[20];
	
	while(1)
	{
		clientfd=accept(sockfd, (struct sockaddr*)&cliaddr, &size);
		
		if(clientfd == -1)
		{
			printf("Cannot accept the message\n");
			exit(0);
		}
		printf("Client connected at IP address: %s and Port number: %i\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
		
		for(;;)
		{
			int r = recv(clientfd, recv1, sizeof(recv1), 0);
			recv1[r] = '\0';
			printf("\n\nMessage from client: %s\n", recv1);
			
			if(strcmp(recv1, "bye") == 0)
			break;
			
			printf("\n\nEnter message to be sent to the client: ");
			scanf("%s",send1);
			send(clientfd, send1, strlen(send1), 0);
		}
	}	
}