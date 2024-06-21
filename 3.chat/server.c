#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 6666
int main()
{
int sockfd,ret;
struct sockaddr_in serveraddr;
int newsocket;
struct sockaddr_in newaddr;
socklen_t addr_size;
char buffer[1024];
pid_t childpid;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd<0)
{
printf("\n Socket creation error \n");
exit(1);
}
printf("socket is created \n");
memset(&serveraddr,'\0',sizeof(serveraddr));
serveraddr.sin_family = AF_INET;
serveraddr.sin_port = htons(PORT);
serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
ret = bind(sockfd, (struct sockaddr*)&serveraddr,
sizeof(serveraddr));
if(ret<0)
{
printf("error in binding \n");
exit(1);
}
printf("binding successful \n");
listen(sockfd,6);
printf("listening------------");
while(1)
{
newsocket=accept(sockfd,(struct sockaddr*)&newaddr,&addr_size);
if(newsocket<0)
{
exit(1);
}
printf("connection accepted from %s:%d\
n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port));
if((childpid=fork())==0)
{

close(sockfd);
while(1)
{
recv(newsocket,buffer,1024,0);
if(strcmp(buffer,":exit")==0)
{
printf("disconnectd from %s:%d\
n",inet_ntoa(newaddr.sin_addr),ntohs(newaddr.sin_port));
break;
}
else
{
printf("client: %s\n",buffer);
send(newsocket,buffer,strlen(buffer),0);
bzero(buffer,sizeof(buffer));
}
}
}
}
close(newsocket);
return 0;
}