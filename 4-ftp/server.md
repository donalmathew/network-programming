#### Code 2: File Transfer Server

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#define SIZE 1024
```

##### 1. Function to Write Received Data to File

```c
void write_file(int sockfd) {
    int n;
    FILE *fp;
    char *filename = "recv.txt"; // File to store received data
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("[-]Error in opening file.");
        exit(1);
    }

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
```

##### 2. Main Function

```c
int main() {
    char *ip = "127.0.0.1"; // Server IP address
    int port = 8080;        // Server port number
    int e;
    int sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[SIZE];
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

##### 5. Bind Socket to IP and Port

```c
e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
if (e < 0) {
    perror("[-]Error in bind");
    exit(1);
}
printf("[+]Binding successful.\n");
```

##### 6. Listen for Incoming Connections

```c
if (listen(sockfd, 10) == 0) {
    printf("[+]Listening....\n");
} else {
    perror("[-]Error in listening");
    exit(1);
}
```

##### 7. Accept Incoming Connection

```c
addr_size = sizeof(new_addr);
new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
```

##### 8. Write Received Data to File

```c
write_file(new_sock);
printf("[+]Data written in the file successfully.\n");

return 0;
}
```

---
