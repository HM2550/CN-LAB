//SERVER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5000

int main(){

	int sockfd, ret;
	struct sockaddr_in serverfd;

	int csocket;
	struct sockaddr_in naddr;

	socklen_t addr_size;

	char buff[1024];
	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
    {
		printf("\nSocket creation failed!");
		exit(1);
	}
	printf("\nSocket creation successful!");

	// memset(&serverfd, '\0', sizeof(serverfd));
	serverfd.sin_family = AF_INET;
	serverfd.sin_port = htons(PORT);
	serverfd.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(sockfd, (struct sockaddr*)&serverfd, sizeof(serverfd));
	if(ret < 0)
    {
		printf("\nBind failed!");
		exit(1);
	}
	printf("\nBind successful!");

	if(listen(sockfd, 10) == 0){
		printf("Error! cannot find any client!\n");
	}
    
    else
    {
		printf("\nListening for incoming client messages!\n");
	}


	while(1)
    {
		csocket = accept(sockfd, (struct sockaddr*)&naddr, &addr_size);
		if(csocket < 0)
        {
			exit(1);
		}
		printf("\n\nConnection accepted from %s:%d\n", inet_ntoa(naddr.sin_addr), ntohs(naddr.sin_port));

		if((childpid = fork()) == 0)
        {
			close(sockfd);

			while(1)
            {
				recv(csocket, buff, 1024, 0);
				if(strcmp(buff, "bye") == 0)
                {
					printf("\n\nDisconnected from %s:%d\n", inet_ntoa(naddr.sin_addr), ntohs(naddr.sin_port));
					break;
				}
                
                else
                {
					printf("\nMessage from client: %s\n", buff);
					send(csocket, buff, strlen(buff), 0);
					bzero(buff, sizeof(buff));
				}
			}
		}

	}

	close(csocket);


	return 0;
}