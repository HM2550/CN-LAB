//Client IOMULTIPLEXING

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include<sys/types.h>
#include<sys/times.h>
#include<netinet/in.h>
#include<netinet/ip.h> 
#include<netdb.h>
#include<arpa/inet.h>

int main(void)
{
	int clientfd, client_size, sockfd;

	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	if(clientfd < 0)
	{
		printf("Socket creation failed!\n");
		return -1;
	}
	printf("Socket created successfully!\n");

	struct sockaddr_in servaddr, cliaddr;
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(2000);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	int c = connect(clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr));  
	
	if(c < 0)
	{
		printf("Connection failed!\n");
		return -1;
	}
	printf("Connection established successfully!\n");
	
	int s; 
	char snd[50];
	
	while(1)
	{
		printf("Enter message to send to server : ");
		scanf("%s", snd);
		
		send(clientfd, snd, strlen(snd), 0);
		if(strcmp(snd, "bye") == 0)
            printf("\nExited successfully\n");
		break;
	}
	
	close(clientfd);
}