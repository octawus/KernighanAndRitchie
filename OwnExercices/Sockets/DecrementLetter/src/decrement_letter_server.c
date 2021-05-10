#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){

    char server_message[256];

    int server_socket;
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    if (server_socket < 0)
        printf("Error in server creating\n");
    else
        printf("Server Created\n");

    struct sockaddr_in server_address, peer_addr;
    server_address.sin_family = AF_UNIX;
    server_address.sin_port = htons(8081);
    server_address.sin_addr.s_addr = INADDR_ANY;
    
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == 0)
        printf("Binded correctly\n");
    else
        printf("Unable to bind\n");

    if (listen(server_socket, 5) == 0)
        printf("Listening ...\n");
    else
        printf("Unable to listen\n");

    socklen_t addr_size;
    addr_size = sizeof(struct sockaddr_in);

    char *ip;

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    printf("Connection Established\n");
    inet_ntop(AF_INET, &(peer_addr.sin_addr), ip, INET_ADDRSTRLEN);

    printf("connection established with IP : %s and PORT : %d\n", 
                                            ip, ntohs(peer_addr.sin_port));

    recv(client_socket, &server_message, sizeof(server_message), 0);

    printf("He recibido la letra: %s \n", server_message);

    close(server_socket);

}