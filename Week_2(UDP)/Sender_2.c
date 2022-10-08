#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h> 
#include<netdb.h>
#include<string.h>

int main()
{
	int sockfd, ret, ret1, ret2, ret3;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd == -1)
	{
		printf("\n\nError in creation of socket\n");
		exit(1);
	}
	
	else
	{
		printf("\n\nCreation of Socket Successful\n");
	}
	
	struct sockaddr_in receiver;
	receiver.sin_family = AF_INET;
	receiver.sin_port = 7500;
	receiver.sin_addr.s_addr = INADDR_ANY;
	
	ret =  bind(sockfd, (const struct sockaddr *)(&receiver),  sizeof(receiver));
	
	if(ret == -1)
	{
		printf("\n\nError in bind\n");
		exit(1);
	}
	
	else
	{
		printf("\n\nBind Successful\n");
	}
		
	char buff1[1024];
	//strcpy(buff1, "\nHI I M aditya\n");
	
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_port = 4500;
	dest.sin_addr.s_addr = INADDR_ANY;
	char msg[50];
	
	char buff2[100];
	struct sockaddr_in src ;
	int len = sizeof(src);
	printf("%s\n",buff1);
	
	while(1)
	{
		printf("\n\nEnter your message 'CLIENT-(1)' : \n\n"); 
		scanf("%s",msg);
		strcpy(buff1,msg);
		
		ret1 = sendto(sockfd, buff1, strlen(buff1), 0, (const struct sockaddr *)(&dest), sizeof(dest));
		printf("\n\nSendto Successful\n\n");

		ret2 = recvfrom(sockfd , buff2 , sizeof(buff2) , 0 , (struct sockaddr*)(&src),(socklen_t*)(&len));
		buff2[ret2] = '\0';
		printf("\n\n%s\n\n",buff2);
		printf("\n\nSuccess in receiving the data\n\n");

		if(strcmp(buff1, "byet") == 0)
    		{
			ret3 = sendto(sockfd, "bye", strlen("bye"), 0, (const struct sockaddr *)(&dest), sizeof(dest));

			if(ret3 == -1)
			{
				printf("\n\nError in sendto\n\n");
				exit(1);
			}

			else
			{
				printf("\n\nExited Successfully\n\n");
				return 0;
			}
		}
	}
	
	//close(sockfd);
	return 0;
}