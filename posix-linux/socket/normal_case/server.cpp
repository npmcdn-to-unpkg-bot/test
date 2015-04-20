#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int sfp,nfp;
    struct sockaddr_in s_add;
    unsigned short port = 8888;
    printf("This is server !\n");

    sfp = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == sfp)
    {
        printf("socket fail ! \n");
        return -1;
    }
    printf("socket ok !\n");

    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = htonl(INADDR_ANY);
    s_add.sin_port = htons(port);

    if(-1 == bind(sfp, (struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
    {
        printf("bind fail !\n");
        return -1;
    }
    printf("bind ok !\n");

    if(-1 == listen(sfp, 5))
    {
        printf("listen fail !\n");
        return -1;
    }
    printf("listen ok\n");

    while(1)
    {
        struct sockaddr_in c_add;
        socklen_t sin_size = sizeof(struct sockaddr_in);

        nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
        if(-1 == nfp)
        {
            printf("accept fail !\n");
            return -1;
        }
        printf("accept ok!\nServer start get connect from %s : %d\n", inet_ntoa(c_add.sin_addr), ntohs(c_add.sin_port));

        const char* hello_msg = "hello,welcome to my server \n";
        if(-1 == write(nfp, hello_msg, strlen(hello_msg) + 1))
        {
            printf("write fail!\n");
            return -1;
        }
        printf("write ok!\n");
        close(nfp);
    }
    close(sfp);
    return 0;
}