#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024

// Function to write received data into a file
void write_file(int sockfd) {
    int n;
    FILE *fp;
    char *filename = "recv.txt"; // File to store received data
    char buffer[SIZE];

    // Open file to write
    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("[-]Error in opening file.");
        exit(1);
    }

    // Receive data from client and write to file
    while (1) {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n <= 0) {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE); // Clear the buffer after writing
    }
    fclose(fp);
    return;
}

int main() {
    char *ip = "127.0.0.1"; // Server IP address
    int port = 8080;        // Server port number
    int e;
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];

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

    // Bind socket to the specified IP and port
    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successful.\n");

    // Listen for incoming connections
    if (listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    } else {
        perror("[-]Error in listening");
        exit(1);
    }

    // Accept incoming connection
    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

    // Write received data to file
    write_file(new_sock);
    printf("[+]Data written in the file successfully.\n");

    // Closing the socket shows error
    

    return 0;
}
