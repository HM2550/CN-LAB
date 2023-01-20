//Server iomultiplexing

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
	int sockfd;
	//, clientfd, client_size;

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
	
	int opt = 1;
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	
	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
	{
		printf("Bind failed!\n");
		return -1;
	}
	printf("Bind successful!\n");

	listen(sockfd, 10);
	
	fd_set readfd, copyfd;
	FD_ZERO(&readfd);
	FD_SET(sockfd, &readfd);
	
	struct timeval tv;
	int maxfd = sockfd+1;
	
	int clientfd[10]; 
	int i=0, j;
	int size = sizeof(servaddr);
	char rcv[50], snd[50];
	int ret;
	
	while(1)
	{
		copyfd = readfd;
		tv.tv_sec = 10;
		tv.tv_usec = 10000000;
		
		ret = select(maxfd, &copyfd, NULL, NULL, &tv);
		if (ret < 0 )
			printf("Select failed!\n");
		if (ret == 0)
			printf("Timeout occured!\n");
			
		else
		{
			if(FD_ISSET(sockfd, &copyfd))
			{
				clientfd[i] = accept(sockfd, (struct sockaddr*)&cliaddr, &size);
				
				if(clientfd[i] == -1)
				{
					printf("Cannot accept the message\n");
					exit(0);
				}
				printf("Client connected at IP address: %s and Port number: %i\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
				
				if(maxfd <= clientfd[i])
				{
					maxfd = clientfd[i] + 1;
					FD_SET(clientfd[i], &readfd);
					i++;
				} 
			}
			
			for(j = 0; j<i; j++)
			{
				if(FD_ISSET(clientfd[j], &copyfd))
				{
					int r = recv(clientfd[j], rcv, sizeof(rcv), 0);
					rcv[r] = '\0';
					
					char ipaddr[50];
					strcpy(ipaddr, inet_ntoa(cliaddr.sin_addr));
					
					if(r == 0)
					{
						printf("%s has disconnected\n", ipaddr);
						close(clientfd[j]);
						FD_CLR(clientfd[j], &readfd);
						break;
					}
					
					printf("Message from client: %s\n", rcv); 
					if(strcmp(rcv, "bye") == 0)
						break;
				}
			}
		}
		
	}
}