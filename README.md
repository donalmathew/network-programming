# Network Programming in C

This repository contains various network programming examples written in C.

## Overview

The codes in this repository are based on [**Beej's Guide to Network Programming**](https://beej.us/guide/bgnet/), which provides a comprehensive introduction to socket programming in C and is a highly recommended resource for anyone interested in network programming. 

Each code file is well-documented with comments explaining the underlying logic, making it easier to understand and modify the programs.

## Contents
---
### 1. TCP Programming
    
#### Client Program :
[[easy to follow steps](/tcp/client.md)] 
[[code](/tcp/client.c)]
#### Server Program :
[[easy to follow steps](/tcp/server.md)]
[[code](/tcp/server.c)]

---

### 2. UDP Programming 
#### Client Program
[[easy to follow steps](/udp/client.md)]
[[code](/udp/client.c)]

#### Server Program
[[easy to follow steps](/udp/server.md)]
[[code](/udp/server.c)]

---

### 3. Multi Server Chat 
#### Client Program
TCP client that connects to a server, sends messages, and receives responses.
[[easy to follow steps](/3.chat/client.md)]
[[code](/3.chat/client.c)]

#### Server Program
TCP server that listens for incoming connections, accepts them, and handles multiple clients using child processes, echoing received messages back to the client.
[[easy to follow steps](/3.chat/server.md)]
[[code](/3.chat/server.c)]



- **File Transfer Protocol** [[code](/tcp/server.md)]
First Code (Client-side): This code implements a file transfer client that connects to a server and sends the contents of a specified file (send.txt) to the server over a TCP connection.

    Second Code (Server-side): This code implements a file transfer server that listens for incoming connections. Upon receiving a connection, it accepts the data sent by the client and writes it to a file (recv.txt).

- **Time Server** [[code](/tcp/server.md)]
- **Stop n Wait** [[code](/tcp/server.md)]
- **Go back n** [[code](/tcp/server.md)]
- **Selective Repeat** [[code](/tcp/server.md)]
- **Distance Vector Routing** [[code](/tcp/server.md)]
- **Leaky Bucket** [[code](/tcp/server.md)]

## How to Use

To compile and run the examples, you can use a standard C compiler like `gcc`. For example:

```bash
gcc -o tcp_server tcp_server.c
./tcp_server
```

Make sure you have the necessary network permissions and tools installed on your system to execute the network programs.



- [code](/tcp/client.md)

https://chatgpt.com/c/e0e59454-6c67-405d-babf-94a3a145f0d2