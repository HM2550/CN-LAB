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
    int ret = connect(sockfd, (struct sockaddr *)&my_socket, sizeof(my_socket));
    if (ret == -1)
    {
        printf("Connection Failure!\n");
        return 0;
    }
    printf("Connected Successfully.\n");
    while (1)
    {
        char buff[100] = {0}, msg[100] = {0};
        strcpy(buff, "");
        printf("Enter the message to be sent:- ");
        scanf("%s", buff);
        ret = send(sockfd, buff, strlen(buff), 0);
        if (ret == -1)
        {
            printf("Failure in Sending the Data.\n");
            return 0;
        }
        ret = recv(sockfd, msg, sizeof(msg), 0);
        if (ret == -1)
        {
            printf("Failure in Receiving the Data.\n");
            return 0;
        }
        printf("Message Received:- %s\n", msg);
        if (strcmp(msg, "Bye") == 0)
            break;
    }
}
