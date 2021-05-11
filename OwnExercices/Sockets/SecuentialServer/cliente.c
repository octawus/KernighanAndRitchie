/*The <unistd.h> header defines miscellaneous symbolic constants
and types, and declares miscellaneous functions.*/
#include <unistd.h>
/*Definitions for network database operations*/
#include <netdb.h>
/*Internet address family*/
#include <netinet/in.h>
/*Main sockets header*/
#include <sys/socket.h>
/*Data type*/
#include <sys/types.h>
/*Definitions for internet operations*/
#include <arpa/inet.h>
/*Standard input/output*/
#include <stdio.h>
/*String operations*/
#include <string.h>
/*Standard library definitions*/
#include <stdlib.h>

#define SERVER_ADDRESS "192.168.0.22"
#define PORT            8080

char buf_tx[100];
char buf_rx[100];

int main()
{
    int sockfd;
    struct sockaddr_in serveraddr;

    /*Socket creation*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        printf("CLIENT: Socket creation failed...\n");
        return -1;
    }
    else
    {
        printf("CLIENT: Socket successfully created...\n");
    }

    memset(&serveraddr, 0, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr( SERVER_ADDRESS );
    serveraddr.sin_port = htons(PORT);

    

    /* try to connect the client socket to server socket */
    if (connect(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) != 0)
    {
        printf("Connection with the server failed...\n");
    }

    printf("Connect to the server..\n");
    write(sockfd, buf_tx, sizeof(buf_tx));
    read(sockfd, buf_rx, sizeof(buf_rx));
    printf("CLIENT: Received: %s \n", buf_rx);

    close(sockfd);
}