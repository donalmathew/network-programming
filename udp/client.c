# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<unistd.h>
# include<sys/types.h>
# include<sys/socket.h>
# include<netinet/in.h>
# include<arpa/inet.h>

int main()
{
    // Message to be sent to the server
    char * hello = "hello from client";

    // Define server address structure
    struct sockaddr_in serveraddr;

    // Create a UDP socket
    int clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(clientsocket == -1)
    {
        perror("socket error \n");
        exit(1);
    }
    printf("client socket created \n");

    // Specify server address and port
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(5555);
    serveraddr.sin_addr.s_addr = INADDR_ANY;

    // Send data to the server
    int len = sendto(clientsocket, (char*)hello, strlen(hello), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if(len == -1)
    {
        perror("failed to send \n");
    }

    // Close the client socket
    close(clientsocket);
    return 0;
}
