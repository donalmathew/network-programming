#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

// Function to simulate message corruption
int isfaulty() {
    int d = rand() % 4; // Generate a random number between 0 and 3
    return (d > 2); // Return true if the number is greater than 2
}

int main() {
    srand(time(0)); // Seed the random number generator

    int c_sock;
    c_sock = socket(AF_INET, SOCK_STREAM, 0); // Create a TCP socket

    struct sockaddr_in client;
    memset(&client, 0, sizeof(client)); // Clear the client address structure

    client.sin_family = AF_INET;
    client.sin_port = htons(9009); // Server port
    client.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    if (connect(c_sock, (struct sockaddr*)&client, sizeof(client)) == -1) {
        printf("Connection failed");
        return 0;
    }

    printf("\n\tClient -with individual acknowledgement scheme\n\n");

    char msg1[50] = "akwnowledgementof-";
    char msg3[50] = "negative akwn-";
    char msg2[50];
    char buff[100];

    int count = -1, flag = 1;

    while (count < 8) {
        bzero(buff, sizeof(buff)); // Clear the buffer
        bzero(msg2, sizeof(msg2)); // Clear the message buffer

        if (count == 7 && flag == 1) {
            flag = 0;
            read(c_sock, buff, sizeof(buff)); // Simulate loss
            continue;
        }

        int n = read(c_sock, buff, sizeof(buff)); // Read the message from the server
        char i = buff[strlen(buff) - 1];
        printf("Message received from server : %s \n", buff);

        int isfault = isfaulty(); // Simulate message corruption

        printf("correption status : %d \n", isfault);

        printf("Response/akwn sent for message \n");
        if (isfault) {
            strcpy(msg2, msg3); // Send a negative acknowledgment if the message is corrupted
        } else {
            strcpy(msg2, msg1); // Send an acknowledgment if the message is correct
            count++;
        }
        msg2[strlen(msg2)] = i; // Append the sequence number
        write(c_sock, msg2, sizeof(msg2)); // Send the acknowledgment
    }

    close(c_sock); // Close the client socket
    return 0;
}
