//CLIENT

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
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	char client_message[1024], server_message[2000];
	char buffer[1024];

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
    {
	    printf("Socket creation failed!");
		exit(1);
	}
    printf("\nSocket creation successful!");

	// memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if(ret < 0)
    {
		printf("\nError connecting to the server!\n");
		exit(1);
	}
	printf("\nConnected to server successfully!\n");

	while(1)
    {
	    printf("\n\nEnter message to send to server:\t");
		scanf("%s", &buffer);
		strcpy(client_message, buffer);
		send(clientSocket, client_message, strlen(client_message), 0);

		if(strcmp(client_message, "bye") == 0)
        {
			close(clientSocket);
			printf("Exited successfully!\n");
			exit(1);
		}

		if(recv(clientSocket, server_message, strlen(client_message), 0) < 0)
        {
			printf("Error in receiving data!\n");
		}
        
        else
        {
			printf("Message from server: %s\n", client_message);
		}
	}

	return 0;
}