#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include <unistd.h>

void main()
{
    // Define the server address structure and buffer for communication
    struct sockaddr_in serveraddr;
    char buffer[1024];

    // Create a socket for the client
    int clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("client socket created successfully \n");

    // Specify server address and port
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("connected to server \n");

    // Prepare and send data to the server
    strcpy(buffer, "hello from client");
    send(clientsocket, buffer, strlen(buffer), 0);

    // Receive data from the server
    recv(clientsocket, buffer, 1024, 0);
    printf("data received: %s \n", buffer);

    // Close the client socket
    close(clientsocket);
}
