#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<net/ethernet.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
void main()
{
int sock_fd,ret;
struct sockaddr_in s;
char msg[100];
sock_fd=socket(AF_INET,SOCK_STREAM,0);
if(sock_fd==-1)
{
printf("Socket not created\n");
exit(1);
}
s.sin_addr.s_addr=INADDR_ANY;
s.sin_port=14;
s.sin_family=AF_INET;
ret=connect(sock_fd,(struct sockaddr*)&s,sizeof(s));
if(ret==-1)
{
printf("Connection failed\n");
exit(1);
}
else
printf("Connected\n");
printf("Enter message to send to server:\n");
gets(msg);
int n=sizeof(s);
ret=sendto(sock_fd,msg,sizeof(msg),0,(const struct sockaddr*)&s,sizeof(s));
if(ret==-1)
{
printf("Message not sent\n");
exit(1);
}
FILE *f;
f=fopen("CText.txt","w");
int flag=0;
while(1)
{
ret=recvfrom(sock_fd,msg,sizeof(msg),0,(struct sockaddr*)&s,&n);
if(ret==-1)
{
printf("Message not received\n");
exit(1);
}
if(strcmp(msg,"Bye")==0)
break;
if(strlen(msg)>0)
{
fputs(msg,f);
flag=1;
}
}
if(flag==1)
{
strcpy(msg,"File received\n");
sendto(sock_fd,msg,sizeof(msg),0,(const struct sockaddr*)&s,sizeof(s));
printf("Message from server:\n");
recvfrom(sock_fd,msg,sizeof(msg),0,(struct sockaddr*)&s,&n);
puts(msg);
}
fclose(f);
close(sock_fd);
}