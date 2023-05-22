#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
//argv[1] dia chi IP
//argv[2] cong may nhan
//argv[3]

int main(int argc, char *argv[])
{
    if(argc <2){
        fprintf(stderr,"providing IP and");
        exit(1);
    }
    int sender = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in addr_send;
    addr_send.sin_family = AF_INET;
    addr_send.sin_addr.s_addr = inet_addr(argv[1]);
    addr_send.sin_port = htons(atoi(argv[2]));

    int recver = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    struct sockaddr_in addr_recver;
    addr_recver.sin_family = AF_INET;
    addr_recver.sin_addr.s_addr = htons(INADDR_ANY);
    addr_recver.sin_port = htons(atoi(argv[3]));

    char buf[256];
    if (bind(recver, (struct sockaddr *)&addr_recver, sizeof(addr_recver)) < 0) {
        printf("Error binding recver");
    }
    fd_set fdread, fdtest;
    FD_ZERO(&fdread);
    FD_SET(STDIN_FILENO, &fdread);
    FD_SET(recver, &fdread);

    while (1) {
        fdtest = fdread;
        int ret = select(recver + 1, &fdtest, NULL, NULL, NULL);
        if (ret < 0)
        {
            perror("select() failed");
            break;
        }

        if (FD_ISSET(STDIN_FILENO, &fdtest))
        {
            fgets(buf, sizeof(buf), stdin);
            sendto(sender, buf, strlen(buf), 0, (struct sockaddr *)&addr_send, sizeof(addr_send));
        }

        if (FD_ISSET(recver, &fdtest))
        {
            ret = recvfrom(recver, buf, sizeof(buf), 0, NULL, NULL);
            if (ret < sizeof(buf)){
                buf[ret] = 0;
            }
            printf("Received: %s\n", buf);
        }

    }
    // Close the socket
    close(sender);
    close(recver);

    return 0;
}