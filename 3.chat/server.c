#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 6666

int main()
{
    int sockfd, ret;
    struct sockaddr_in serveraddr;
    int newsocket;
    struct sockaddr_in newaddr;
    socklen_t addr_size;
    char buffer[1024];
    pid_t childpid;

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("\n Socket creation error \n");
        exit(1);
    }
    printf("socket is created \n");

    // Initialize server address structure
    memset(&serveraddr, '\0', sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket to the specified IP and port
    ret = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (ret < 0) {
        printf("error in binding \n");
        exit(1);
    }
    printf("binding successful \n");

    // Listen for incoming connections
    listen(sockfd, 6);
    printf("listening------------");

    while (1) {
        // Accept an incoming connection
        newsocket = accept(sockfd, (struct sockaddr*)&newaddr, &addr_size);
        if (newsocket < 0) {
            exit(1);
        }
        printf("connection accepted from %s:%d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));

        // Create a child process to handle the new connection
        if ((childpid = fork()) == 0) {
            // In the child process, close the listening socket
            close(sockfd);
            while (1) {
                // Receive messages from the client
                recv(newsocket, buffer, 1024, 0);
                if (strcmp(buffer, ":exit") == 0) {
                    printf("disconnected from %s:%d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));
                    break;
                } else {
                    printf("client: %s\n", buffer);
                    // Echo the message back to the client
                    send(newsocket, buffer, strlen(buffer), 0);
                    bzero(buffer, sizeof(buffer));
                }
            }
        }
    }
    // Close the new socket (this is only reached in the parent process)
    close(newsocket);
    return 0;
}
