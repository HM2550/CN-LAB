// #include<stdio.h>
// #include<stdlib.h>
// #include<sys/types.h>
// #include<sys/socket.h>
// #include<netinet/in.h>
// #include<netinet/ip.h> 
// #include<netdb.h>
// #include<string.h>

// int main()
// {
// 	int sockfd, ret, ret1, ret2;
	
// 	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

// 	if (sockfd == -1)
// 	{
// 		printf("\n\nError in creation of socket\n\n");
// 		exit(1);
// 	}

// 	else
//     {
// 		printf("\n\nCreation  of Socket Successful\n\n");
//     }
	
// 	struct sockaddr_in receiver;
// 	receiver.sin_family = AF_INET;
// 	receiver.sin_port = 6000;
// 	receiver.sin_addr.s_addr = INADDR_ANY;
	
// 	ret =  bind(sockfd, (const struct sockaddr *)(&receiver),  sizeof(receiver));
	
// 	if(ret == -1)
// 	{
// 		printf("\n\nError in bind\n\n");
// 		exit(1);
// 	}
	
// 	else
// 	{
// 		printf("\nBind Successful\n\n");
// 	}
		
// 	char buff1[1024];
// 	//strcpy(buff1, "\nHI I M aditya\n");
	
// 	struct sockaddr_in dest;
// 	dest.sin_family = AF_INET;
// 	dest.sin_port = 5000;
// 	dest.sin_addr.s_addr = INADDR_ANY;
// 	char msg[50];
// 	scanf("%s",msg);
// 	strcpy(buff1,msg);
	
// 	ret1 = sendto(sockfd, buff1, strlen(buff1), 0, (const struct sockaddr *)(&dest), sizeof(dest));
	
// 	if(ret1 == -1)
// 	{
// 		printf("\n\nError in sendto\n\n");
// 		exit(1);
// 	}
	
// 	else
// 	{
// 		printf("\nSendto Successful\n\n");
// 	}
	
// 	char buff2[100];
//     struct sockaddr_in src ;
//     int len = sizeof(src);
//     printf("%s\n",buff1);
//     ret2 = recvfrom(sockfd , buff2 , sizeof(buff2) , 0 , (struct sockaddr*)(&src),(socklen_t*)(&len));
//     if(ret2 == -1) 
//     {
//         printf("\n\nFailure in recieving the data\n");
//         exit(1);
//     }

//     else 
//     {
//         printf("\n\nSuccess in recieving the data\n");
//         printf("\n\n%s\n",buff2);
//     }	
// }