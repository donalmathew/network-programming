### 0. initialise buffer
>char //string
```c
char buffer[1024];
```

### 1. initialize adresses
>struct sockaddr_in
```c
struct sockaddr_in serveraddr,clientaddr;
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
### 4. bind (2) and (3) (//only for server)
>int
```c
bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
```

### 5. listen and accept (//only in tcp)
 - #### 5.1 - listen
 >int
 ```c
 listen(serversocket,6); //6 is max number of requests
 ```

 - #### 5.2 - accept
 >int
 ```c
 //here sizeof(clientaddr) is accepted as pointer
 int addrsize=sizeof(clientaddr); //reference in (1)
 int newsocket= accept(serversocket,(struct sockaddr*)&clientaddr,&addrsize);
 ```
- second socket is created here, used for send and recv 
### 6. recv and send
> ssize_t - length of message
```c
recv(newsocket,buffer,1024,0); //here instead of 1024, strlen(buffer) can be used
```
```c
strcpy(buffer,"hello from server");
send(newsocket,buffer,1024,0);
```

### 7. close the socket
>int
```c
close(newsocket);
```