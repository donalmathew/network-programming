#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

// Function to send the file to the server
void send_file(FILE *fp, int sockfd) {
    int n;
    char data[SIZE] = {0};

    // Read data from file and send to server
    while (fgets(data, SIZE, fp) != NULL) {
        if (send(sockfd, data, sizeof(data), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE); // Clear the buffer after sending
    }
}

int main() {
    char *ip = "127.0.0.1"; // Server IP address
    int port = 8080;        // Server port number
    int e;
    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "send.txt"; // File to be sent

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    // Configure server address struct
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Connect to the server
    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e == -1) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    // Open file to read
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("[-]Error in reading file.");
        exit(1);
    }

    // Send file to the server
    send_file(fp, sockfd);
    printf("[+]File data sent successfully.\n");

    // Close the connection
    printf("[+]Closing the connection.\n");
    close(sockfd);

    return 0;
}
