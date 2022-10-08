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
    int sockfd , ret , ret1 , ret2 ;
    sockfd = socket( AF_INET , SOCK_DGRAM , 0 );
    if(sockfd == -1)
    {
    printf("\n\nSocket creation failed\n");
    exit(1);
    }
    else printf("\n\nSocket creation success\n");
    
    struct sockaddr_in my_socket ;
    my_socket.sin_family = AF_INET ;
    my_socket.sin_port = 5000 ;
    my_socket.sin_addr.s_addr = INADDR_ANY ;
    
    ret = bind( sockfd , (const struct sockaddr *)(&my_socket) , sizeof(my_socket) );
    if(ret == -1)
    {
    printf("\nBind failure\n");
    exit(1);
    }
    else printf("\n\nBind Success\n") ;
    
    char buff1[100];
    struct sockaddr_in src ;
    int len = sizeof(src);
    
    ret1 = recvfrom(sockfd , buff1 , sizeof(buff1) , 0 , (struct sockaddr*)(&src) , (socklen_t*)(&len));
    if(ret1 == -1) 
    {
    printf("\n\nFailure in recvfrom\n");
    exit(1);
    }
    else 
    {
    printf("\n\nSuccess in recvfrom\n");
    printf("\n\n%s\n",buff1);
    }
    
    char buff2[100] ;
    //strcpy(buff2,"\nHello\n");
    struct sockaddr_in dest ;
    dest.sin_family = AF_INET ;
    dest.sin_port = 6000 ;
    dest.sin_addr.s_addr = INADDR_ANY ;
    //printf("%s\n",buff2);
    char msg[50];
    scanf("%s",msg);
    strcpy(buff2,msg);	 
    
    ret2 = sendto(sockfd , buff2 , strlen(buff2) , 0 , (const struct sockaddr *)(&dest) , sizeof(dest));
    if(ret2 == -1) 
    {
        printf("\n\nFailure in sendto\n");
        exit(1);
    }

    else 
    {
        printf("\n\nSuccess in sendto\n");
    }	  

    return 0;
}