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

    recbytes = 0;
    int i = -1;
    do {
        i = read(fd, buffer, 1024);
        if (i == -1) {
            printf("read error\n");
            return -1;
        }

        if (i == 0) {
            printf("nothing read\n")
        } else {
            recbytes += i;
            printf("receive %d, all received %d\n", i, recbytes);

            if (recbytes == 20 *1024 *1024)
                break;
        }
    } while (i >= 0)

    close(fd);
    return 0;
}