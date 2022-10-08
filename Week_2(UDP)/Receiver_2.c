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
    int sockfd , ret , ret1 , ret2, ret3;
    sockfd = socket( AF_INET , SOCK_DGRAM , 0 );

    if(sockfd == -1)
    {
        printf("\n\nSocket creation failed\n");
        bye(1);
    }

    else 
    {
        printf("\n\nSocket creation success\n");
    }

    struct sockaddr_in my_socket ;
    my_socket.sin_family = AF_INET ;
    my_socket.sin_port = 4500 ;
    my_socket.sin_addr.s_addr = INADDR_ANY ;
    
    ret = bind( sockfd , (const struct sockaddr *)(&my_socket) , sizeof(my_socket) );
    if(ret == -1)
    {
        printf("\nBind failure\n");
        bye(1);
    }

    else 
    {
        printf("\n\nBind Success\n") ;
    }

    char buff1[100];
    struct sockaddr_in src ;
    int len = sizeof(src);
    
    char buff2[100] ;
    //strcpy(buff2,"\nHello\n");
    struct sockaddr_in dest ;
    dest.sin_family = AF_INET ;
    dest.sin_port = 7500 ;
    dest.sin_addr.s_addr = INADDR_ANY ;
    //printf("%s\n",buff2);
    char msg[50];	 

    while(1)
    {
        ret1 = recvfrom(sockfd , buff1 , sizeof(buff1) , 0 , (struct sockaddr*)(&src) , (socklen_t*)(&len));
        buff1[ret1] = '\0';
        printf("\n\n%s\n\n",buff1);
        printf("\n\nSuccess in receiving the data\n\n");
        
        printf("\n\nEnter your message 'RECEIVER-(2)' : \n\n"); 
        scanf("%s",msg);
        strcpy(buff2,msg);

        ret2 = sendto(sockfd , buff2 , strlen(buff2) , 0 , (const struct sockaddr *)(&dest) , sizeof(dest));
        printf("\n\nSuccess in sending the data\n");
        
        if(strcmp(buff2, "bye") == 0)
        {
            ret3 = sendto(sockfd , "bye", strlen("bye") , 0 , (const struct sockaddr *)(&dest) , sizeof(dest));
            printf("\n\nExited Successfully\n");
            return 0;	
        }	  
    }
    //close(sockfd);
    return 0;
}