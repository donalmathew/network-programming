#### Code 1: File Transfer Client

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024
```

##### 1. Function to Send File to the Server

```c
void send_file(FILE *fp, int sockfd) {
    int n;
    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp) != NULL) {
        if (send(sockfd, data, sizeof(data), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE); // Clear the buffer after sending
    }
}
```

##### 2. Main Function

```c
int main() {
    char *ip = "127.0.0.1"; // Server IP address
    int port = 8080;        // Server port number
    int e;
    int sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "send.txt"; // File to be sent
```

##### 3. Create Socket

```c
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
}
printf("[+]Server socket created successfully.\n");
```

##### 4. Configure Server Address

```c
server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);
```

##### 5. Connect to the Server

```c
e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
if (e == -1) {
    perror("[-]Error in socket");
    exit(1);
}
printf("[+]Connected to Server.\n");
```

##### 6. Open and Send File

```c
fp = fopen(filename, "r");
if (fp == NULL) {
    perror("[-]Error in reading file.");
    exit(1);
}

send_file(fp, sockfd);
printf("[+]File data sent successfully.\n");
```

##### 7. Close Connection

```c
printf("[+]Closing the connection.\n");
close(sockfd);

return 0;
}
```

