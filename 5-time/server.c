#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define S_PORT 43454 // Server port
#define C_PORT 43455 // Client port
#define ERROR -1     // Error code
#define IP_STR "127.0.0.1" // IP address

int main(int argc, char const *argv[]) {
    int sfd, num;
    time_t current_time;
    struct sockaddr_in servaddr, clientaddr;

    // Create UDP socket
    sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sfd == ERROR) {
        perror("Could not open a socket");
        return 1;
    }

    // Initialize server address struct
    memset((char *)&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(S_PORT);

    // Initialize client address struct
    memset((char *)&clientaddr, 0, sizeof(clientaddr));
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_addr.s_addr = inet_addr(IP_STR);
    clientaddr.sin_port = htons(C_PORT);

    // Bind the socket to the server address and port
    if ((bind(sfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) {
        perror("Could not bind socket");
        return 2;
    }

    printf("Server is running on %s:%d\n", IP_STR, S_PORT);

    // Main loop to handle incoming client requests
    while (1) {
        recvfrom(sfd, &num, sizeof(num), 0, (struct sockaddr *)&clientaddr, (socklen_t *)&clientaddr);

        // Get the current time
        current_time = time(NULL);
        printf("Client at %s:%d asked for time: %s\n",
               inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), ctime(&current_time));

        // Send the current time to the client
        sendto(sfd, &current_time, sizeof(current_time), 0, (struct sockaddr *)&clientaddr, sizeof(clientaddr));
    }

    return 0;
}
