#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

int main()
{

    // create a socket https://man7.org/linux/man-pages/man2/socket.2.html
    // AF_UNIX = AF_LOCAL
    // SOCK_STREAM = TCP
    // SOCK_DGRAM = UDP
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an adress for the socket https://man7.org/linux/man-pages/man7/ip.7.html
    // basic ip does not supply port numbers 
    // they are implemented by higher level protocols(TCP/UDP). 
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    
    /* htons = host to network short
    resolves problems regarding "endianness"
    On little endian systems (Like this one --Linux-- ), 
    the first bit is the 0 bit (least significant bit --LSB--)
    the last bit is the n bit (most significant bit --MSB--)
    in this case, the network protocol uses big endian ordering
    so a conversion is needed.
    The port numbers below 1024 are called privileged ports (or
    sometimes: reserved ports).  Only a privileged process (on Linux:
    a process that has the CAP_NET_BIND_SERVICE capability in the
    user namespace governing its network namespace) may bind to
    these sockets. 
    */

    server_address.sin_port = htons(24500);

    // s_addr member of in_addr should be assigned one of the INADDR_* values. 
    // INADDR_ANY (0.0.0.0) and INADDR_BROADCAST (255.255.255.255)
    // are byte-order-neutral. It should be adapted to network byte order
    // in any other case. https://man7.org/linux/man-pages/man7/ip.7.html

    server_address.sin_addr.s_addr = INADDR_ANY;

    // The socket "network_socket" gets connected to the addres specified in "server_address".
    int connection_status = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // If conection succeeds zero is returned, on error -1 is returned.
    if (connection_status == -1)
    {
        printf("There was an error establishing the remote socket\n\n");
        printf("%d", errno);
    }

    // receive data from server
    char server_response[256];

    // receive a message from a socket, and returns the lenght of the message on
    // successful completion. If a message is too long to fit in the supplied
    // buffer, excess bytes may be discarded depending on the type of
    // socket the message is received from.
    
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // print out the server's response
    printf("The server sent the data: %s\n", server_response);

    close(network_socket);
    return 0;
}