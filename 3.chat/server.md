
### 0. Include Header Files
```c
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
```

### 1. Define Port Number
```c
#define PORT 6666
```

### 2. Main Function
```c
int main() {
    int sockfd, ret;
    struct sockaddr_in serveraddr;
    int newsocket;
    struct sockaddr_in newaddr;
    socklen_t addr_size;
    char buffer[1024];
    pid_t childpid;
```

### 3. Create a TCP Socket
```c
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
    printf("\n Socket creation error \n");
    exit(1);
}
printf("socket is created \n");
```

### 4. Initialize Server Address Structure
```c
memset(&serveraddr, '\0', sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
serveraddr.sin_port = htons(PORT);
serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
```

### 5. Bind the Socket to the IP and Port
```c
ret = bind(sockfd, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
if (ret < 0) {
    printf("error in binding \n");
    exit(1);
}
printf("binding successful \n");
```

### 6. Listen for Incoming Connections
```c
listen(sockfd, 6);
printf("listening------------");
```

### 7. Accept an Incoming Connection
```c
newsocket = accept(sockfd, (struct sockaddr*)&newaddr, &addr_size);
if (newsocket < 0) {
    exit(1);
}
printf("connection accepted from %s:%d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));
```

### 8. Handle the New Connection with a Child Process
```c
if ((childpid = fork()) == 0) {
    close(sockfd); // In child process, close the listening socket
    while (1) {
        // Receive messages from the client
        recv(newsocket, buffer, 1024, 0);
        if (strcmp(buffer, ":exit") == 0) {
            printf("disconnected from %s:%d\n", inet_ntoa(newaddr.sin_addr), ntohs(newaddr.sin_port));
            break;
        } else {
            printf("client: %s\n", buffer);
            // Echo the message back to the client
            send(newsocket, buffer, strlen(buffer), 0);
            bzero(buffer, sizeof(buffer));
        }
    }
}
```

### 9. Close the Socket (Parent Process)
```c
close(newsocket);
return 0;
}
```

