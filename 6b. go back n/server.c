#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define WINDOW_SIZE 4

// Define a structure for the Packet
typedef struct Packet {
    int seq_num; // Sequence number of the packet
    char data[1024]; // Data of the packet
} Packet;

// Function to receive packets from the client
void receivePackets(int serverSocket, struct sockaddr_in clientAddr, int totalPackets) {
    int expectedSeqNum = 0; // Sequence number of the expected packet
    while (expectedSeqNum < totalPackets) {
        Packet receivedPacket;
        int clientAddrLen = sizeof(clientAddr);
        
        // Receive a packet from the client
        int bytesReceived = recvfrom(serverSocket, (char *)&receivedPacket, sizeof(Packet), 0, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (bytesReceived == -1) {
            perror("recvfrom");
            continue; // Continue to the next iteration if there's an error
        }
        
        // Check if the received packet is the expected one
        if (receivedPacket.seq_num == expectedSeqNum) {
            printf("Received packet with seq_num %d\n", receivedPacket.seq_num);
            
            // Simulate sending an acknowledgment packet
            Packet ackPacket;
            ackPacket.seq_num = expectedSeqNum;
            sendto(serverSocket, (char *)&ackPacket, sizeof(Packet), 0, (struct sockaddr *)&clientAddr, sizeof(clientAddr));
            expectedSeqNum++; // Increment the expected sequence number
        } else {
            printf("Received out-of-order packet with seq_num %d, expected %d\n", receivedPacket.seq_num, expectedSeqNum);
        }
    }
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket
    
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Server port
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address
    
    bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); // Bind the socket to the address and port
    
    int totalPackets = 10; // Total number of packets to receive
    struct sockaddr_in clientAddr;
    
    // Call the function to receive packets
    receivePackets(serverSocket, clientAddr, totalPackets);
    
    return 0;
}
