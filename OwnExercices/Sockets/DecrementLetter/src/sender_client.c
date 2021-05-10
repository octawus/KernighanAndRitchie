#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){

    int server_socket;
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);

    struct  sockaddr_in server_address;
    server_address.sin_family = AF_UNIX;

    server_address.sin_port = htons(8081);
    server_address.sin_addr.s_addr = INADDR_ANY;

    int connection_status = connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (connection_status == -1)
    {
        printf("There was an error establishing the remote socket\n\n");
    }

    char message[256];

    printf("Escribe una letra\n");
    scanf("%s", message);

    send(server_socket, message, sizeof(message), 0);
    // recv(server_socket, &message, sizeof(message), 0);

    close(server_socket);
}