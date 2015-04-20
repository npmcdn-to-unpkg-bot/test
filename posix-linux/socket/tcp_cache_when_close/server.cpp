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

    // bind right away.
    int on = 1;
    setsockopt( sfp, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

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

        printf("We are going to send 20M data\n");

        int buffer_size = 1900;
        char *buffer = new char[buffer_size];
        for (int i=0; i< buffer_size; i++)
            buffer[i] = 'a';

        for  (int i=0 ; i <100; i++) {
            int left = buffer_size;
            while (left > 0) {
                int i = write(nfp, buffer, buffer_size);
                if (i == -1) {
                    printf("write failed\n");
                    exit(-1);
                }
                if (i == 0) {
                    printf("return 0, nothing write\n");
                } else {
                    printf("write %d data\n", i);
                    left -= i;
                }
            }
        }
        printf("write ok! close socket\n");
        close(nfp);
        break;
    }
    close(sfp);
    return 0;
}