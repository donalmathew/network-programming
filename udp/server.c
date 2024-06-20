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
    // Buffer to store received data
    char buffer[50];

    // Define server address structure
    struct sockaddr_in servaddr;

    // Create a UDP socket
    int serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    if(serversocket == -1)
    {
        perror("socket error \n");
        exit(1);
    }
    printf("server socket created \n");

    // Specify server address and port
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5555);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the specified address and port
    int rc = bind(serversocket, (struct sockaddr*)&servaddr, sizeof(servaddr));
    if(rc == -1)
    {
        perror("bind error \n");
        exit(1);
    }
    printf("bind to port number \n");

    // Receive data from the client
    socklen_t len = 0;
    int n = recvfrom(serversocket, (char *)buffer, 50, MSG_WAITALL, 0, &len);
    printf("%s", buffer);

    // Close the server socket
    close(serversocket);
    return 0;
}
