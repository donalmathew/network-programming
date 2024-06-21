#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 6666
int main()
{
int clientsocket, ret;
struct sockaddr_in serveraddr;
char buffer[1024];
clientsocket = socket(AF_INET, SOCK_STREAM, 0);
if(clientsocket<0)
{
perror("socket failed \n");
exit(EXIT_FAILURE);
}
printf("socket created successfully \n");
memset(&serveraddr,'\0',sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
serveraddr.sin_port = htons(PORT);
ret=connect(clientsocket, (struct sockaddr*)&serveraddr,
sizeof(serveraddr));
if(ret<0)
{
printf("error in connection \n");
exit(EXIT_FAILURE);
}
printf("connected to server \n");
while(1)
{
printf("client \t");
scanf("%s",buffer);
send(clientsocket,buffer,strlen(buffer),0);
if(strcmp(buffer,":exit")==0)
{
close(clientsocket);
printf("disconnected from server \n");
exit(1);
}
if(recv(clientsocket,buffer,1024,0)<0)
{
printf("error in receving data \n");
}
else
{
printf("server: \t%s\n",buffer);
}

}
return 0;
}