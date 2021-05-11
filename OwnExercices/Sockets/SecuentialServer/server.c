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
/*Number of last error*/
#include <errno.h>
/*Standard input/output*/
#include <stdio.h>
/*String operations*/
#include <string.h>

/*Defined server constants*/
#define SERV_PORT 8080
#define SERV_HOST_ADDR "192.168.0.22"
#define BUF_SIZE 100
#define BACKLOG 5


int main(int argc, char* argv[])
{
    int sockfd, connfd;
    unsigned int len;
    struct sockaddr_in servaddr, client;

    int len_rx, len_tx = 0;
    char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    char buff_rx[BUF_SIZE];

    /*Create a socket (file descriptor-int-) 
    for an internet aplications using TCP protocol*/
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /*Assert that the socket creation has been succesfull*/
    if(sockfd == -1)
    {
        fprintf(stderr, "[SERVER-error]: socket creation failed. %d: %s \n", errno, strerror( errno ));
    }

    /*Initializae the whole servaddr struct to 0.*/
    memset(&servaddr, 0, sizeof(servaddr));

    /*Define the type of addresses that your socket can comunicate with. In this case
    AF_INET means IPv4 addresses*/
    servaddr.sin_family = AF_INET;
    /*Define the actual address, in this case IP. One of the constant defined earlier is used*/
    servaddr.sin_addr.s_addr = inet_addr(SERV_HOST_ADDR);
    /*Define the port. One of the constant defined earlier is used*/
    servaddr.sin_port = htons(SERV_PORT);

    /*Try to bind the socket and the address. 
    If the binding is not succesfull, print error*/
    if((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    }
    else
    {
        printf("[SERVER]: Socket successfully binded \n");
    }

    /*Start listening  to the socket. If fail to listen, print error*/
    if ((listen(sockfd, BACKLOG)) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket listen failed. %d: %s \n", errno, strerror( errno ));
        return -1;
    }
    else
    {
        printf("[SERVER]: Listening on SERV_PORT %d \n\n", ntohs(servaddr.sin_port));
    }


    len = sizeof(client);

    while(1)
    {
        /*Accept next conection and open a new socket to comunicate with it.
        If the conection is not correctly established, print error, else start RX/TX*/
        connfd = accept(sockfd, (struct sockaddr *)&client, &len);
        if(connfd < 0)
        {
            fprintf(stderr, "[SERVER-error]: connection not accepted. %d: %s \n", errno, strerror( errno ));
            return -1;
        }
        else
        {
            while(1)
            {   
                /*Start reading data into buff_rx. Returns -1 if reading fails.
                Else if lengh is 0 (Nothing to read) close the socket. Else if lenght
                is bigger than 0 write the initialize defined string to the client.*/
                len_rx = read(connfd, buff_rx, sizeof(buff_rx));
                if(len_rx == -1)
                {
                    fprintf(stderr, "[SERVER-error]: connfd cannot read. %d: %s\n", errno, strerror( errno ));
                }
                else if (len_rx == 0)
                {
                    printf("[SERVER]: client socket closed \n\n");
                    close(connfd);
                    break;
                }
                else
                {
                    write(connfd, buff_tx, strlen(buff_tx));
                    printf("[SERVER]: %s \n", buff_rx);
                }

            }
        }
    }
}
