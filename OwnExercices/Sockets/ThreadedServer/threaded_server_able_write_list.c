/* The <unistd.h> header defines miscellaneous symbolic constants
and types, and declares miscellaneous functions.*/
#include <unistd.h>
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
/*Standard library definitions*/
#include <stdlib.h>
/*Thread library*/
#include <pthread.h>
/*Signals*/
#include <signal.h>
#include <linux/list.h>
#include <assert.h>

#define MAX_CLIENTS 10
#define BUFFER_SZ 2048
#define NAME_LEN 32

LIST_HEAD(hnode);

/*For _Atomic: https://en.cppreference.com/w/c/language/atomic*/
static _Atomic unsigned int cli_count = 0;
static int uid = 10;

//Client structure

typedef struct client{
    struct sockaddr_in address;
    int sockfd;
    int uid;
    char name[NAME_LEN];
    struct  list_head list_member; 
} client_t;

/*Initializae a mutex to default parameters.

What is a mutex? https://stackoverflow.com/questions/34524/what-is-a-mutex

When I am having a big heated discussion at work, I use a rubber chicken 
which I keep in my desk for just such occasions. The person holding the 
chicken is the only person who is allowed to talk. If you don't hold the 
chicken you cannot speak. You can only indicate that you want the chicken 
and wait until you get it before you speak. Once you have finished speaking, 
you can hand the chicken back to the moderator who will hand it to the next 
person to speak. This ensures that people do not speak over each other, 
and also have their own space to talk.

Replace Chicken with Mutex and person with thread and you basically have 
the concept of a mutex.

What are the default parameters? http://www.skrenta.com/rt/man/pthread_mutex_init.3.html

The  LinuxThreads  implementation  supports only one mutex
attributes, the mutex  kind,  which  is  either  ``fast'',
``recursive'',  or ``error checking''. The kind of a mutex
determines whether it can be locked again by a thread that
already  owns  it.   The  default  kind  is  ``fast''.

what does ``fast'' mean? https://medium.com/@jaydesai36/types-of-mutex-in-linux-6536d3b849ab

Care has been taken to ensure that the default values of the mutex 
attributes have been defined such that mutexes initialized with the 
defaults have simple enough semantics so that the locking and 
unlocking can be done with the equivalent of a test-and-set instruction 
(plus possibly a few other basic instructions).

A default (``fast'') mutex usually does not record or check thread 
ownership. This means that mutex locked by one thread can unlock 
by another thread (This problem is solved by the "error cheking" type)
*/

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

int find_and_delete(int argUid, struct list_head * head)
{
    struct list_head *iter;
    struct client *objPtr;

    __list_for_each(iter, head){
        objPtr = list_entry(iter, struct client, list_member);
        if (objPtr -> uid == argUid)
        {
            list_del(&objPtr->list_member);
            free(objPtr);
            return 1;
        }
    }

    return 0;
}

// CUIDADO AQUI CON LO QUE DEVUELVO, NO SE SI ESTA BIEN HECHO!!!
struct client * add_client(struct sockaddr_in argAdress, int argSockfd, int argUid, struct list_head *head){
    struct client *clientPtr = (struct client *)malloc(sizeof(struct client));
    assert(clientPtr != NULL);

    clientPtr -> address = argAdress;
    clientPtr -> sockfd = argSockfd;
    clientPtr -> uid = argUid;

    INIT_LIST_HEAD(&clientPtr -> list_member);
    list_add(&clientPtr -> list_member, head);

    return clientPtr;
}

void send_message_list(char * s, int argUid, struct list_head * head){

    struct list_head *iter;
    struct client *objPtr;

    pthread_mutex_lock(&clients_mutex);

    __list_for_each(iter, head){
        objPtr = list_entry(iter, struct client, list_member);
        assert(objPtr != NULL);
        if(objPtr -> uid != argUid){
            if(write(objPtr -> sockfd, s, strlen(s)) < 0){
                printf("[SERVER-error]: write to descriptor failed\n");
                break;
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);

}

/* TODO: Implement this array (and everything related to it) 
with a Singly Linked List
Posible documentation:
https://www.geeksforgeeks.org/data-structures/linked-list/singly-linked-list/
https://www.hackerearth.com/practice/data-structures/linked-list/singly-linked-list/tutorial/
https://www.geeksforgeeks.org/linked-list-set-1-introduction/
*/
/*Static arrays get initialized to 0*/
/*The array is made with pointer to structs so that functions can operate over the same
array.*/
client_t *clients[MAX_CLIENTS];

/* \r escape sequence means "carriage return". It moves the cursor to 
the start of the line*/

void str_overwrite_stdout(){
    printf("\r%s", "> ");
    fflush(stdout);
}

void str_trim_lf(char* arr, int lenght){
    for(int i = 0; i < lenght; i++){
        if(arr[i] == '\n'){
            arr[i] = '\0';
            break;
        }
    }
}

/*The ! operator only return True if the operand is 0*/

/*Example to understand this function
Lets suppose s_addr 192.168.123.43 =
11000000.10101000.01111011.00101011

First line:
11000000.10101000.01111011.00101011
& (bitwise mult)
00000000.00000000.00000000.11111111
=
00101011 = 43

Second line:
11000000.10101000.01111011.00101011
&
00000000.00000000.11111111.00000000
=
01111011.0000000 = 123.0 (>> 8 moves this value to the right 8 positions)
01111011.0000000 >> 8 = 01111011 = 123.

Third line: 
11000000.10101000.01111011.00101011
&
00000000.11111111.00000000.00000000
=
10101000.00000000.00000000 = 168.0.0
10101000.00000000.00000000 >> 16 = 10101000 = 168

Forth line: 
11000000.10101000.01111011.00101011
&
11111111.00000000.00000000.00000000
=
111000000.00000000.00000000.00000000 = 192.0.0.0
111000000.00000000.00000000.00000000 >> 24 = 111000000 = 192
*/
void print_ip_addr(struct sockaddr_in addr){
    printf("%d.%d.%d.%d",
            addr.sin_addr.s_addr & 0xff,
            (addr.sin_addr.s_addr & 0xff00) >> 8,
            (addr.sin_addr.s_addr & 0xff0000) >> 16,
            (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

void* handle_client(void *arg){
    char buffer[BUFFER_SZ];
    char name[NAME_LEN];
    int leave_flag = 0;
    cli_count ++;

    client_t *cli = (client_t*)arg;

    // Name
    if(recv(cli -> sockfd, name, NAME_LEN, 0) <= 0 || strlen(name) < 2 || strlen(name) >= NAME_LEN - 1){
        printf("[SERVER-error]: Write a valid name \n");
        leave_flag = 1;
    } else {
        strcpy( cli -> name, name);
        sprintf(buffer, "%s has joined\n", cli -> name);
        printf("%s", buffer);
        send_message_list(buffer, cli -> uid, &hnode);
    }

    bzero(buffer, BUFFER_SZ);
    while(1){
        if(leave_flag){
            break;
        }
        int received = recv(cli -> sockfd, buffer, BUFFER_SZ, 0);
        if (received > 0){
            if(strlen(buffer) > 0){
                send_message_list(buffer, cli -> uid, &hnode);
                str_trim_lf(buffer, strlen(buffer));
                printf("%s -> %s", buffer, cli -> name);
            }
        } else if (received == 0 || strcmp(buffer, "exit") == 0){
            sprintf(buffer, "%s has left\n", cli -> name);
            printf("%s", buffer);
            send_message_list(buffer, cli -> uid, &hnode);
            leave_flag = 1;
        }else {
            printf("[SERVER-error]: Error during message receive.\n");
            leave_flag = 1;
        }
        bzero(buffer, BUFFER_SZ);
    }
    close(cli -> sockfd);
    find_and_delete(cli -> uid, &hnode);
    cli_count --;
    pthread_detach(pthread_self());

    return NULL;
}

void handle_connections(void *arg){
    int connfd = 0;
    struct sockaddr_in cli_addr;
    pthread_t tid;
    

    int *listenfd = (int *)arg;

    while (1)
    {
        socklen_t clilen = sizeof(cli_addr);

        connfd = accept(*listenfd, (struct sockaddr*)&cli_addr, &clilen);
        if(connfd == -1){
            printf("[SERVER-error]: Could not accept the connection: %d: %s \n", errno, strerror( errno ));
        }
        //Check for max client.
        if((cli_count + 1) == MAX_CLIENTS){
            printf("[SERVER-warning]: Maximum number of clients reached. Connection rejected\n");
            print_ip_addr(cli_addr);
            close(connfd);
        }

        client_t *cli = add_client(cli_addr, connfd, uid++, &hnode);
        
        pthread_create(&tid, NULL, handle_client, (void *)cli);

    }   
}

void send_msg_handler(){
    char buffer[BUFFER_SZ] = {};
    char message[BUFFER_SZ + NAME_LEN + 2] = {};
    char name[NAME_LEN] = "Server";

    while (1)
    {

        str_overwrite_stdout();
        fgets(buffer, BUFFER_SZ, stdin);
        str_trim_lf(buffer, BUFFER_SZ);

        if(strcmp(buffer, "exit") == 0){
            break;
        } else {
            sprintf(message, "%s: %s\n", name, buffer);
            send_message_list(message, 0, &hnode);
        }

        bzero(buffer, BUFFER_SZ);
        bzero(message, BUFFER_SZ + NAME_LEN);
    }
     //catch_ctrl_c_and_exit(2);
}

int main(int argc, char **argv)
{
    if(argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);
    int err;

    int option = 1;
    int listenfd = 0;
    int *plistenfd = &listenfd;
    struct  sockaddr_in serv_addr;

    /* If signal SIGPIPE reaches this process, ignore.
    A SIGPIPE is sent to a process if it tried to write 
    to a socket that had been shutdown for writing or isn't 
    connected (anymore)*/

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    signal(SIGPIPE, SIG_IGN);

    /*
    int setsockopt(int socket, int level, int option_name,
       const void *option_value, socklen_t option_len);
    The setsockopt() function shall set the option specified by the 
    option_name argument, at the protocol level specified by the level 
    argument, to the value pointed to by the option_value argument for 
    the socket associated with the file descriptor specified by the 
    socket argument.
    SOL_SOCKET:   When manipulating socket options, the level at which the 
                  option resides and the name of the option must be specified. 
                  To manipulate options at the sockets API level, level is 
                  specified as SOL_SOCKET.
    SO_REUSEPORT: Permits multiple AF_INET or AF_INET6 sockets to be bound
                  to an identical socket address.  This option must be set
                  on each socket (including the first socket) prior to
                  calling bind(2) on the socket.  To prevent port hijacking,
                  all of the processes binding to the same address must have
                  the same effective UID.  This option can be employed with
                  both TCP and UDP sockets.
    SO_REUSEADDR: Indicates that the rules used in validating addresses
                  supplied in a bind(2) call should allow reuse of local
                  addresses.  For AF_INET sockets this means that a socket
                  may bind, except when there is an active listening socket
                  bound to the address.  When the listening socket is bound
                  to INADDR_ANY with a specific port then it is not possible
                  to bind to this port for any local address.  Argument is
                  an integer boolean flag.
    */

    if(setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char*)&option, sizeof(option)) < 0){
        printf("[SERVER-error]: Socket configuration failed. %d: %s\n", errno, strerror( errno ));
        return EXIT_FAILURE;
    }

    if(bind(listenfd, (struct  sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("[SERVER-error]: Binding failed. %d: %s\n", errno, strerror( errno ));
        return EXIT_FAILURE;
    }

    if(listen(listenfd, 10) < 0)
    {
        printf("[SERVER-error]: Listening failed. %d: %s\n", errno, strerror( errno ));
        return EXIT_FAILURE;
    }

    printf("|==========| WELCOME TO THE CHAT |==========|\n");

    pthread_t connection_thread;
    if((err = pthread_create(&connection_thread, NULL, (void*)handle_connections, (void *) plistenfd)) != 0){
        printf("[SERVER-error]: Error during conection handling: %d: %s\n", errno, strerror( errno ));
        return EXIT_FAILURE;
    }

    pthread_t message_thread;
    if((err = pthread_create(&message_thread, NULL, (void*)send_msg_handler, NULL)) != 0){
        printf("[SERVER-error]: Error during message broadcast handling: %d: %s\n", errno, strerror( errno ));
        return EXIT_FAILURE;
    }

    while(1){
       

        // Reduce CPU usage
        sleep(1);
    }
}