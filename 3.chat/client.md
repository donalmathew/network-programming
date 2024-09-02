### 0. Include Header Files
```c
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
```

### 1. Define Port Number
```c
#define PORT 6666
```

### 2. Main Function
```c
int main() {
    int clientsocket, ret;
    struct sockaddr_in serveraddr;
    char buffer[1024];
```

### 3. Create a TCP Socket
```c
clientsocket = socket(AF_INET, SOCK_STREAM, 0);
if (clientsocket < 0) {
    perror("socket failed \n");
    exit(EXIT_FAILURE);
}
printf("socket created successfully \n");
```

### 4. Initialize Server Address Structure
```c
memset(&serveraddr, '\0', sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
serveraddr.sin_port = htons(PORT);
```

### 5. Connect to the Server
```c
ret = connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
if (ret < 0) {
    printf("error in connection \n");
    exit(EXIT_FAILURE);
}
printf("connected to server \n");
```

### 6. Communication Loop
```c
while (1) {
    // Read message from user input
    printf("client \t");
    scanf("%s", buffer);

    // Send message to the server
    send(clientsocket, buffer, strlen(buffer), 0);

    // Exit if the ":exit" command is received
    if (strcmp(buffer, ":exit") == 0) {
        close(clientsocket);
        printf("disconnected from server \n");
        exit(1);
    }

    // Receive message from the server
    if (recv(clientsocket, buffer, 1024, 0) < 0) {
        printf("error in receiving data \n");
    } else {
        printf("server: \t%s\n", buffer);
    }
}
return 0;
}
```

### 7. Close the Socket
```c
close(clientsocket);
```

--- 
