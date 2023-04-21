#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
// provides required data types
#include <sys/types.h>
// holds address family and socket functions
#include <sys/socket.h>
// has the sockaddr_in structure
#include <netinet/in.h>
// has functions for read and write operations
#include <fcntl.h>
// basic C header
#include <stdio.h>
// header to help with strings
#include <string.h>
// has macros such as EXIT_FAILURE
#include<stdlib.h>
// port through which connection is to be made
#define CONNECTION_PORT 3050
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
// structure to represent the address
    struct sockaddr_in server_address;
// Message to be sent to the server
    char* message="This is a message from the client";
// storage buffer to receive messages
    char buffer[255];
    if(argc <1){
        fprintf(stderr,"port no provided.... try again");
        exit(1);
    }
// create an Ipv4 and TCP socket
    int socket_descriptor = socket(AF_INET,SOCK_STREAM,0);
// Check whether the socket is created successfully
    if(socket_descriptor<0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }  
    int status=0;
// initialize address structure for binding
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(CONNECTION_PORT);
// set address to any address available
    server_address.sin_addr.s_addr =INADDR_ANY;
    server_address.sin_zero[8]='\0';
// connect to the server
    status=connect(socket_descriptor,(struct sockaddr*)&server_address, sizeof(server_address));
    if(status<0)
    {
        perror("Couldn't connect with the server");
        exit(EXIT_FAILURE);
    }    
    int n;
    FILE *fp = fopen(argv[3], "r");
    if (fp == NULL)
    {
        printf("Error opening the file sv_log.txt");
        return -1;
    }
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    char str[255];
    sprintf(str, "%d", sz);
    write(socket_descriptor, str, 255);
    fseek(fp,0L,SEEK_SET);
    while(!feof(fp)){
        bzero(buffer,255);
        fgets(buffer,255,fp);
        write(socket_descriptor,buffer,strlen(buffer));
    }
    close(socket_descriptor);
    return 0;
}