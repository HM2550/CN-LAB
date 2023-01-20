//SERVER FORK

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444

int main()
{
	int serverfd, ret;
	struct sockaddr_in serveraddr;

	int newfd;
	struct sockaddr_in newaddr;
    char server_message[2000];

	socklen_t addr_size;

	char client_message[1024];
	pid_t childpid;

	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd < 0)
    {
		printf("\nSocket creation failed!");
		exit(1);
	}
	printf("\nSocket creation successful!");

	// memset(&serveraddr, '\0', sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = bind(serverfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
	if(ret < 0)
    {
	    printf("\nBind failed!");
		exit(1);
	}
	printf("\nBind successful!");

	if(listen(serverfd, 10) == 0)
    {
		printf("\nListening for incoming client messages!\n");
	}

    else
    {
        printf("Error! cannot find any client!\n");
	}


	while(1)
    {
		newfd = accept(serverfd, (struct sockaddr*)&newaddr, &addr_size);
		if(newfd < 0)
        {
			exit(1);
		}
		printf("\n\nConnection accepted from %s:%d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));

		if((childpid = fork()) == 0)
        {
			close(serverfd);

			while(1)
            {
				recv(newfd, client_message, 1024, 0);
				if(strcmp(client_message, "bye") == 0)
                {
					printf("\nDisconnected from %s:%d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));
					break;
				}
                
                else
                {
					printf("\nMessage from client: %s\n", client_message);
                    char msg[50];
		            printf("\n\nEnter message to send to client:\t");
                    // scanf("%s",msg);
                    // strcpy(server_message, msg);
					// send(newfd, server_message, strlen(server_message), 0);
					send(newfd, client_message, strlen(client_message), 0);
					bzero(client_message, sizeof(client_message));
				}
			}
		}

	}
	close(newfd);

	return 0;
}