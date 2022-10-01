#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Socket Creation Failed.");

        return 0;
    }
    printf("Socket Creation Successful.\n");
    struct sockaddr_in my_socket;
    my_socket.sin_family = AF_INET;
    my_socket.sin_port = htons(6000);
    my_socket.sin_addr.s_addr = inet_addr("172.30.214.141");
    int ret = bind(sockfd, (const struct sockaddr *)(&my_socket), sizeof(struct sockaddr));
    if (ret == -1)
    {
        printf("Bind Failure!\n");
        return 0;
    }
    printf("Bind Successful.\n");
    listen(sockfd, 5);

    struct sockaddr_in src;
    int len = sizeof(struct sockaddr);
    int acc = accept(sockfd, (struct sockaddr *)&src, (socklen_t *)&len);
    if (acc == -1)
    {
        printf("Accept Failure.\n");
        return 0;
    }
    printf("Accepted Successful.\n");
    while (1)
    {
        char buff[100]={0}, msg1[100]={0};
        ret = recv(acc, msg1, 100, 0);
        if (ret == -1)
        {
            printf("Failure in Receiving data.\n");
            return 0;
        }
        printf("Message Received:- %s\n", msg1);
        printf("Enter the message to be sent:- ");
        scanf(" %s", buff);
        ret = send(acc, buff, strlen(buff), 0);
        if (ret == -1)
        {
            printf("Failure in Sending the Data.\n");
            return 0;
        }
        if (strcmp(buff, "Bye") == 0)
            break;
        strcpy(buff, "");
    }
}