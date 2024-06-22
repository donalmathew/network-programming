#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

// Function to resend a message if a timeout or error occurs
void rsendd(int ch, int c_sock) {
    char buff2[60];
    bzero(buff2, sizeof(buff2)); // Clear the buffer
    strcpy(buff2, "reserver message :");
    buff2[strlen(buff2)] = (ch) + '0'; // Append the sequence number
    buff2[strlen(buff2)] = '\0';
    printf("Resending Message to client :%s \n", buff2);
    write(c_sock, buff2, sizeof(buff2)); // Send the message
    usleep(1000); // Small delay
}

int main() {
    int s_sock, c_sock;
    s_sock = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket

    struct sockaddr_in server, other;
    memset(&server, 0, sizeof(server)); // Clear the server address structure
    memset(&other, 0, sizeof(other)); // Clear the client address structure

    server.sin_family = AF_INET;
    server.sin_port = htons(9009); // Server port
    server.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address

    socklen_t add;
    if (bind(s_sock, (struct sockaddr *)&server, sizeof(server)) == -1) {
        printf("Binding failed\n");
        return 0;
    }

    printf("\tServer Up\n Selective repeat scheme\n\n");
    listen(s_sock, 10); // Listen for incoming connections

    add = sizeof(other);
    c_sock = accept(s_sock, (struct sockaddr *)&other, &add); // Accept a connection

    time_t t1, t2;
    char msg[50] = "server message :";
    char buff[50];
    int flag = 0;

    fd_set set1;
    struct timeval timeout1;
    int rv1, rv2, rv3;
    int tot = 0;
    int ok[20];
    memset(ok, 0, sizeof(ok)); // Clear the array

    while (tot < 9) {
        int toti = tot;
        for (int j = (0 + toti); j < (3 + toti); j++) {
            bzero(buff, sizeof(buff)); // Clear the buffer
            char buff2[60];
            bzero(buff2, sizeof(buff2)); // Clear the buffer
            strcpy(buff2, "server message :");
            buff2[strlen(buff2)] = (j) + '0'; // Append the sequence number
            buff2[strlen(buff2)] = '\0';
            printf("Message sent to client :%s \n", buff2);
            write(c_sock, buff2, sizeof(buff2)); // Send the message
            usleep(1000); // Small delay
        }

        for (int k = 0 + toti; k < (toti + 3); k++) {
            qq: // Label for goto statement
            FD_ZERO(&set1);
            FD_SET(c_sock, &set1);

            timeout1.tv_sec = 2; // Set timeout to 2 seconds
            timeout1.tv_usec = 0;

            rv1 = select(c_sock + 1, &set1, NULL, NULL, &timeout1); // Wait for activity on the socket

            if (rv1 == -1) {
                perror("select error ");
            } else if (rv1 == 0) {
                printf("Timeout for message :%d \n", k);
                rsendd(k, c_sock); // Resend the message if timeout occurs
                goto qq; // Go back to the start of the loop
            } else {
                read(c_sock, buff, sizeof(buff)); // Read the acknowledgment
                printf("Message from Client: %s\n", buff);
                if (buff[0] == 'n') {
                    printf(" corrupt message awk (msg %d) \n", buff[strlen(buff) - 1] - '0');
                    rsendd((buff[strlen(buff) - 1] - '0'), c_sock); // Resend the message if it's corrupted
                    goto qq; // Go back to the start of the loop
                } else {
                    tot++;
                }
            }
        }
    }

    close(c_sock); // Close the client socket
    close(s_sock); // Close the server socket
    return 0;
}
