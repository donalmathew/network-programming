#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#define WINDOW_SIZE 4

// Define a structure for the Packet
typedef struct Packet {
    int seq_num; // Sequence number of the packet
    char data[1024]; // Data of the packet
} Packet;

// Function to send packets to the server
void sendPackets(int clientSocket, struct sockaddr_in serverAddr, int totalPackets) {
    int base = 0; // Base of the window
    int nextSeqNum = 0; // Next sequence number to be sent
    int totalFramesSent = 0; // Total number of frames sent
    
    while (base < totalPackets) {
        // Send packets within the window
        while (nextSeqNum < base + WINDOW_SIZE && nextSeqNum < totalPackets) {
            Packet packet;
            packet.seq_num = nextSeqNum;
            sendto(clientSocket, (char *)&packet, sizeof(Packet), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
            printf("Sending Frame %d...\n", packet.seq_num);
            totalFramesSent++;
            nextSeqNum++;
        }
        
        fd_set ackSet;
        FD_ZERO(&ackSet);
        int i;
        for (i = base; i < nextSeqNum; i++) {
            FD_SET(clientSocket, &ackSet);
        }
        
        struct timeval timeout;
        timeout.tv_sec = 5; // Set the timeout to 5 seconds
        timeout.tv_usec = 0;
        
        int ready = select(0, &ackSet, NULL, NULL, &timeout); // Wait for acknowledgment
        
        if (ready == -1) {
            perror("select");
        } else if (ready == 0) {
            // Timeout occurred, retransmit the window
            printf("Timeout!! Frame Number : %d Not Received\n", base);
            printf("Retransmitting Window...\n");
            nextSeqNum = base; // Retransmit from the base of the window
        } else {
            // Process received acknowledgments
            for (i = base; i < nextSeqNum; i++) {
                if (FD_ISSET(clientSocket, &ackSet)) {
                    Packet ackPacket;
                    int serverAddrLen = sizeof(serverAddr);
                    int bytesReceived = recvfrom(clientSocket, (char *)&ackPacket, sizeof(Packet), 0, (struct sockaddr *)&serverAddr, &serverAddrLen);
                    if (bytesReceived == -1) {
                        perror("recvfrom");
                    } else {
                        printf("Acknowledgment for Frame %d...\n", ackPacket.seq_num);
                        base++; // Move the window base
                    }
                }
            }
        }
        printf("Total number of frames transmitted are : %d\n", totalFramesSent);
    }
}

int main() {
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Server port
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address
    
    int totalPackets = 10; // Total number of packets to send
    
    // Call the function to send packets
    sendPackets(clientSocket, serverAddr, totalPackets);
    
    return 0;
}
