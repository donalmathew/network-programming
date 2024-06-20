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
char buffer[50];
struct sockaddr_in servaddr;
int serversocket = socket(AF_INET,SOCK_DGRAM,0);
if(serversocket == -1)
{
perror("socket error \n");
exit(1);
}
printf("server socket created \n");
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(5555);
servaddr.sin_addr.s_addr = INADDR_ANY;
int rc = bind(serversocket,(struct sockaddr*)&servaddr,sizeof(servaddr));
if(rc == -1)
{
perror("bind error \n");
exit(1);
}
printf("bind to port number \n");
socklen_t len = 0;
int n = recvfrom(serversocket, (char *)buffer,50,MSG_WAITALL,0,&len);
printf("%s",buffer);
close(serversocket);
return 0;
}