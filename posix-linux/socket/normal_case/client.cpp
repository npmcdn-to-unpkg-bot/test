#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int fd;
    int recbytes;
    int sin_size;
    char buffer[1024] = { 0 };   
    struct sockaddr_in add;
    // IP and port.
    int port = 8888; 
    const char* ip = "127.0.0.1";

    printf("This is client !\n");

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == fd)
    {
        printf("socket fail !\n");
        return -1;
    }
    printf("socket ok !\n");

    bzero(&add,sizeof(struct sockaddr_in));
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr(ip);
    add.sin_port = htons(port);
    printf("try to connect addr = %s ,port : %d\n", ip, port);

    if(-1 == connect(fd,(struct sockaddr *)(&add), sizeof(struct sockaddr)))
    {
        printf("connect fail! error:%s\n", strerror(errno));
        return -1;
    }
    printf("connect ok !\n");

    if(-1 == (recbytes = read(fd,buffer,1024)))
    {
        printf("read data fail !\n");
        return -1;
    }
    printf("read ok\nREC:\n");
    buffer[recbytes]='\0';
    printf("%s\n",buffer);
    getchar();
    close(fd);
    return 0;
}