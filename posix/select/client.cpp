#include <string>
#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <assert.h>
#include <errno.h>
#include <strings.h>

static std::vector<int> g_connect_fds;
static const unsigned MAX_CONNECTIONS = 5;

void init_net();

int main(int argc, char** argv) {

    init_net();
    assert(g_connect_fds.size() == MAX_CONNECTIONS);

    fd_set read_fds;
    fd_set write_fds;
    struct timeval timeout = {3, 0}; //select等待3秒，3秒轮询，要非阻塞就置0
    char buffer[256] = { 0 }; //256字节的接收缓冲区

    while (true) {
        std::cout << "loop start ....." << std::endl;
        FD_ZERO(&write_fds);      //每次循环都要清空集合，否则不能检测描述符变化
        int maxfd = 0;
        for (int i=0; i < g_connect_fds.size(); i++) {
            int fd = g_connect_fds[i];
            FD_SET(fd, &write_fds); //添加描述符
            if (maxfd < fd) {
                maxfd = fd;
            }
        }
 
        maxfd++; //描述符最大值加1
        switch(select(maxfd, NULL, &write_fds, NULL, NULL)) {  
        case -1:
            exit(-1);
            break; 
        case 0:
            break;
        default:
            {
                for (int i=0; i < g_connect_fds.size(); i++) {
                    int fd = g_connect_fds[i];
                    if(FD_ISSET(fd, &write_fds)) { //测试sock是否可读，即是否网络上有数据
                        memset(buffer, 256, 0);
                        sprintf(buffer, "This is fd %d", fd);
                        write(fd, buffer, strlen(buffer)+1);
                        std::cout << "fd " << fd << " is writing" << std::endl;
                    } 
                }
            }
            break;
        }

        // sleep 1
        sleep(10);
    }
}

void init_net()
{
    std::cout << "This is client" << std::endl;

    unsigned short port = 7890;
    const char* ip = "127.0.0.1";

    struct sockaddr_in add;
    bzero(&add,sizeof(struct sockaddr_in));
    add.sin_family = AF_INET;
    add.sin_addr.s_addr = inet_addr(ip);
    add.sin_port = htons(port);

    // As client.
    for (int i =0; i < MAX_CONNECTIONS; i++) {
        int fd = socket(AF_INET, SOCK_STREAM, 0);
        if (-1 == fd) {
            std::cout << "Socket failed" << std::endl;
            exit(-1);
        }

        if(-1 == connect(fd,(struct sockaddr *)(&add), sizeof(struct sockaddr))) {
            printf("%d, connect fail! error:%s\n", i, strerror(errno));
            exit(-1);
        }
        printf("%d connect ok!\n", i);

        g_connect_fds.push_back(fd);
    }
}
