#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
void main()
{
struct sockaddr_in serveraddr,clientaddr;
char buffer[1024];
int serversocket = socket(AF_INET,SOCK_STREAM,0);
printf("server socket created successfully \n");
serveraddr.sin_family = AF_INET;
serveraddr.sin_port = htons(4444);
serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
printf("bind to port number \n");
listen(serversocket,6);
printf("listening------------\n");
int addrsize = sizeof(clientaddr);
int newsocket=accept(serversocket,(struct sockaddr *)&clientaddr,&addrsize);
recv(newsocket,buffer,1024,0);
printf("data received: %s \n",buffer);
strcpy(buffer,"hello from server");
send(newsocket,buffer,strlen(buffer),0);
}