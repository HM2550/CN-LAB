//Reciever Side #
// gcc reciever.c -o recv
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> 

struct Packet{
   int seqno;
   char buff[100];
};

int main()
{
    int serverfd, ret;
    struct Packet pkt;

    serverfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(serverfd == -1)
    {
        printf("Socket creation failed!");
        exit(1);
    }
    
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = 5000;
    saddr.sin_addr.s_addr = INADDR_ANY;
    
    ret = bind(serverfd, (const struct sockaddr*)(&saddr),sizeof(saddr));
    
    if(ret == -1)
    {
        printf("Bind Failure");
        exit(1);
    }
    
    while(1)
    {
        //here
        // Recieving the file
        struct sockaddr_in recv_sock;
        int len = sizeof(recv_sock);
        ret = recvfrom(serverfd,&pkt,sizeof(pkt),0,(struct sockaddr*)(&recv_sock),(socklen_t*)(&len));
        if(ret == -1){
            printf("Failure in reciving the data!");
            exit(1);
        }
        else
        {
            printf("\nPacket successfully recieved!");
            printf("\nSequence number of packet : %d ",pkt.seqno);
            printf("\nMessage within the packet : %s ",pkt.buff);
        }
         
        // Sending the file
        int ack = (pkt.seqno+1)%2;
        
        struct sockaddr_in dest;
        dest.sin_family = AF_INET;
        dest.sin_port = 6000;
        dest.sin_addr.s_addr = INADDR_ANY;
        
        ret = sendto(serverfd, &ack, sizeof(ack), 0, (const struct sockaddr*)(&dest),sizeof(dest));
        if(ret == -1)
        {
            printf("Failure in sending the data!");
            exit(1);
        }

        else
        {
            printf("\nAcknowledgement with ACK Number %d is sent!",ack);
        }
        // here
    }

    return 0;
}