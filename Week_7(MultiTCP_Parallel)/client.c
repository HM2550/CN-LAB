//CLIENT

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

	int clientfd, ret;
	struct sockaddr_in saddr;
	char buff[1024];

	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	if(clientfd < 0){
		printf("Socket creation failed!");
		exit(1);
	}
	printf("\nSocket creation successful!");

	// memset(&saddr, '\0', sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(PORT);
	saddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientfd, (struct sockaddr*)&saddr, sizeof(saddr));
	if(ret < 0){
		printf("\nError connecting to the server!\n");
		exit(1);
	}
	printf("\nConnected to server successfully!\n");

	while(1){
		printf("\n\nEnter message to send to server:\t");
		scanf("%s", &buff[0]);
		send(clientfd, buff, strlen(buff), 0);

		if(strcmp(buff, "bye") == 0){
			close(clientfd);
			printf("Exited successfully!\n");
			exit(1);
		}

		if(recv(clientfd, buff, 1024, 0) < 0){
			printf("Error in receiving data!\n");
		}else{
			printf("Message from server: \t%s\n", buff);
		}
	}

	return 0;
}