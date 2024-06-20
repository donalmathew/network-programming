# include<stdio.h>
# include<stdlib.h>
# include<string.h>
# include<unistd.h>
# include<sys/types.h>
# include<sys/socket.h>
# include<netinet/in.h>
# include<arpa/inet.h>
int main()
{
char * hello = "hello from client";
struct sockaddr_in serveraddr;
int clientsocket = socket(AF_INET,SOCK_DGRAM,0);
if(clientsocket == -1)
{
perror("socket error \n");
exit(1);
}
printf("server socket created \n");
serveraddr.sin_family = AF_INET;
serveraddr.sin_port = htons(5555);
serveraddr.sin_addr.s_addr = INADDR_ANY;
int len = sendto(clientsocket, (char*)hello,strlen(hello),0,(struct
sockaddr*)&serveraddr,sizeof(serveraddr));
if(len == -1)
{
perror("failed to send \n");
}
close(clientsocket);
return 0;
}