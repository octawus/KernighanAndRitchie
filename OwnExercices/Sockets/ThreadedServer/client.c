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

#define MAX_CLIENTS 10
#define BUFFER_SZ 2048
#define NAME_LEN 32

/* volatile tells the compiler not to optimize 
anything that has to do with the volatile variable.

There are at least three common reasons to use it, 
all involving situations where the value of the 
variable can change without action from the visible 
code: When you interface with hardware that changes 
the value itself; when there's another thread running 
that also uses the variable; or when there's a signal 
handler that might change the value of the variable.*/

volatile sig_atomic_t flag = 0;

int sockfd = 0;
char name[NAME_LEN];

void str_overwrite_stdout(){
    printf("\r%s", "> ");
    fflush(stdout);
}

void str_trim_lf(char* arr, int length){
    for(int i = 0; i < length; i++){
        if(arr[i] == '\n'){
            arr[i] = '\0';
            break;
        }
    }
}

void catch_ctrl_c_and_exit(){
    flag = 1;
}

int main(int argc, char **argv){

    if(argc != 2){
        printf("[ERROR-client]: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *ip = "127.0.0.1";
    char port = atoi(argv[1]);

    signal(SIGINT, catch_ctrl_c_and_exit);

    printf("Enter your name: ");
    fgets(name, NAME_LEN, stdin);
    str_trim_lf(name, strlen(name));

    if(strlen(name) > NAME_LEN - 1 || strlen(name) < 2){
        printf("[CLIENT-error]: Write a valid name\n");
    return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    //Connect to the server
    int err = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(err == -1){
        printf("[CLIENT-error]: Could not connect to the server: %d: %s \n", errno, strerror( errno ));
        return EXIT_FAILURE;
    }

    //Send the name

    send(sockfd, name, NAME_LEN, 0);

    printf("|==========| WELCOME TO THE CHAT |==========|\n");



    return EXIT_SUCCESS;
}