### 0. initialise buffer
>char //string
```c
char buffer[1024];
```

### 1. initialize adresses
>struct sockaddr_in
```c
struct sockaddr_in serveraddr;
```

### 2. socket creation
>int
```c
int serversocket = socket(AF_INET,SOCK_STREAM,0);
```
- socket type: ipv4,tcp

### 3. ip and port are initialised
>struct sockaddr_in 
```c
serveraddr.sin_family=AF_INET;
serveraddr.sin_port=htons(4444); //host to server (big or little endian)
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
```
### 4. connect (2) and (3). (//similar to bind) 
>int
```c
connect(clientsocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
```

### 5. send and recv
> ssize_t - length of message
```c
strcpy(buffer,"hello from server");
send(newsocket,buffer,1024,0);
```
```c
recv(newsocket,buffer,1024,0); //here instead of 1024, strlen(buffer) can be used
```

### 7. close the socket
>int
```c
close(newsocket);
```