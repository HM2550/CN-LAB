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
	int sock,sock_fd,ret;
	struct sockaddr_in s,c;
	char msg[100];
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==-1)
	{
		printf("Socket not created\n");
		exit(1);
	}
	s.sin_addr.s_addr=INADDR_ANY;
	s.sin_port=14;
	s.sin_family=AF_INET;
	ret=bind(sock,(const struct sockaddr*)&s,sizeof(s));
	if(ret==-1)
	{
		printf("Bind failure\n");
		exit(1);
	}
	listen(sock,1);
	int c1=sizeof(struct sockaddr_in);
	sock_fd=accept(sock,(struct sockaddr*)&c,(socklen_t *)&c1);
	if(sock_fd==-1)
	{
		printf("Acceptance failed\n");
		exit(1);
	}
	else
		printf("Connection accepted\n");
	int n=sizeof(c);
	ret=recvfrom(sock_fd,msg,sizeof(msg),0,(struct sockaddr*)&c,&n);
	printf("Message from client:\n");
	puts(msg);
	FILE *f;
	int flag=0;
	system("ls>SText.txt");
	f=fopen("SText.txt","r");
	while(fgets(msg,100,f))
	{
		sendto(sock_fd,msg,sizeof(msg),0,(const struct sockaddr*)&c,sizeof(c));
		flag=1;
	}
	strcpy(msg,"Bye");
	if(flag==1)
	{
		sendto(sock_fd,msg,sizeof(msg),0,(const struct sockaddr*)&c,sizeof(c));
		strcpy(msg,"File sent");
		sendto(sock_fd,msg,sizeof(msg),0,(const struct sockaddr*)&c,sizeof(c));
		recvfrom(sock_fd,msg,sizeof(msg),0,(struct sockaddr*)&c,&n);
		printf("Message from client:\n");
		printf("%s\n",msg);
	}
	fclose(f);
}