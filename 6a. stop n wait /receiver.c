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
    int sockfd;
    struct sockaddr_in serveraddr, newaddr;
    char buffer[1024];
    int frame_id = 0;    // Frame sequence number
    frame frame_send;    // Frame to be sent
    frame frame_recv;    // Frame received from the client

    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // Create a UDP socket

    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(6666); // Server port
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address

    bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr)); // Bind the socket to the address and port

    while(1) {
        socklen_t addr_size = sizeof(newaddr);
        int f_recv_size = recvfrom(sockfd, &frame_recv, sizeof(frame), 0, (struct sockaddr*)&newaddr, &addr_size); // Receive frame from client
        if(f_recv_size > 0 && frame_recv.frame_kind == 1 && frame_recv.seq_no == frame_id) {
            // Check if the received frame is a data frame with the expected sequence number
            printf("[+] Frame received: %s\n", frame_recv.packet.data);
            frame_send.seq_no = 0; // Sequence number for acknowledgment frame
            frame_send.frame_kind = 0; // Acknowledgment frame
            frame_send.ack = frame_recv.seq_no + 1; // Acknowledgment number
            sendto(sockfd, &frame_send, sizeof(frame), 0, (struct sockaddr*)&newaddr, addr_size); // Send acknowledgment frame to client
            printf("[+] Ack sent\n");
        } else {
            printf("[+] Frame not received\n");
        }
        frame_id++; // Increment frame sequence number
    }
    //close(sockfd); // Close the socket
}
