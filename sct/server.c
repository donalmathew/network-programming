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
    // Define the server and client address structures and buffer for communication
    struct sockaddr_in serveraddr, clientaddr;
    char buffer[1024];

    // Create a socket for the server
    int serversocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("server socket created successfully \n");

    // Specify server address and port
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(4444);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind the socket to the specified address and port
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("bind to port number \n");

    // Listen for incoming connections
    listen(serversocket, 6);
    printf("listening------------\n");

    // Accept an incoming connection
    int addrsize = sizeof(clientaddr);
    int newsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &addrsize);

    // Receive data from the client
    recv(newsocket, buffer, 1024, 0);
    printf("data received: %s \n", buffer);

    // Prepare and send data to the client
    strcpy(buffer, "hello from server");
    send(newsocket, buffer, strlen(buffer), 0);

    // Close the new socket and the server socket
    close(newsocket);
}
