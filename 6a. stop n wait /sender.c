#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

// Define a structure for the packet
typedef struct packet {
    char data[1024];
} packet;

// Define a structure for the frame
typedef struct frame {
    int frame_kind;  // 1 for data frame, 0 for acknowledgment frame
    int seq_no;      // Sequence number of the frame
    int ack;         // Acknowledgment number
    packet packet;   // The actual data packet
} frame;

void main() {
    struct sockaddr_in serveraddr;
    char buffer[1024];
    int frame_id = 0;    // Frame sequence number
    frame frame_send;    // Frame to be sent
    frame frame_recv;    // Frame received from the server
    int ack_recv = 1;    // Flag to indicate if acknowledgment is received
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(6666); // Server port
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    while(1) {
        if(ack_recv == 1) { // Send new frame only if acknowledgment is received
            frame_send.seq_no = frame_id;
            frame_send.frame_kind = 1; // Data frame
            frame_send.ack = 0; // No acknowledgment in data frame
            printf("Enter data: ");
            scanf("%s", buffer); // Read data from user
            strcpy(frame_send.packet.data, buffer); // Copy data to the frame
            sendto(sockfd, &frame_send, sizeof(frame), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); // Send frame to server
            printf("[+] Frame sent\n");
        }

        int addr_size = sizeof(serveraddr);
        int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(frame), 0, (struct sockaddr*)&serveraddr, &addr_size); // Receive frame from server
        if(f_recv_size > 0 && frame_recv.seq_no == 0 && frame_recv.ack == frame_id + 1) {
            // Check if the received frame is an acknowledgment for the sent frame
            printf("[+] Ack received\n");
            ack_recv = 1; // Set acknowledgment received flag
        } else {
            printf("[+] Ack not received\n");
            ack_recv = 0; // Set acknowledgment not received flag
        }
        frame_id++; // Increment frame sequence number
    }
    //close(sockfd); // Close the socket
}
