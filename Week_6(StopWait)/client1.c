//Senders Side #
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
    int clientfd, ret;
    struct Packet pkt; // Packet Declaration

    clientfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(clientfd == -1)
    {
        printf("Socket creation failed!");
        exit(1);
    }
    
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = 6000;
    saddr.sin_addr.s_addr = INADDR_ANY;
    
    ret = bind(clientfd, (const struct sockaddr*)(&saddr),sizeof(saddr));
    
    if(ret == -1)
    {
        printf("Bind Failure!");
        exit(1);
    }
    
    pkt.seqno = 1;
    int flag =0;

    while(1)
    {    
        if(flag != 1)
        {
            pkt.seqno = (pkt.seqno+1)%2;
        }

        else
        { 
            flag = 0; 
        }
            
        // Sending the Packet
        char msg[100];
        printf("\nEnter your message : \n");
        scanf("%s",msg);
        strcpy(pkt.buff,msg);
        
        // sizeof(buf) -----> 100 so we will not use this one
        // strlen(buf) -----> 
        struct sockaddr_in dest;
        dest.sin_family = AF_INET;
        dest.sin_port = 5000;
        dest.sin_addr.s_addr = INADDR_ANY;
        
        ret = sendto(clientfd, &pkt, sizeof(pkt), 0, (const struct sockaddr*)(&dest),sizeof(dest));
        
        if(ret == -1)
        {
            printf("Failure in sending the data!");
            exit(1);
        }

        else
        {
            printf("\nPacket sent successfully!");
            printf("\nSequence number of packet: %d ",pkt.seqno);
            printf("\nMessage within packet: %s ",pkt.buff);
        }
        
        
        // Recieving the Acknowledgment 
        int ack;
        
        struct sockaddr_in recv_sock;
        int len = sizeof(recv_sock);
        
        ret = recvfrom(clientfd,&ack,sizeof(ack),0,(struct sockaddr*)(&recv_sock),(socklen_t*)(&len));
        
        printf("\nAcknowledgement recieved with ACK Number : %d",ack);
        
        if(ack!=(pkt.seqno+1)%2)
        {
            flag = 1;
        } 
    //here
    }

    return 0;
}