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

static int g_fd;
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
        FD_ZERO(&read_fds);      //每次循环都要清空集合，否则不能检测描述符变化
        FD_ZERO(&write_fds);
        int maxfd = 0;
        for (int i=0; i < g_connect_fds.size(); i++) {
            int fd = g_connect_fds[i];
            if (maxfd < fd) {
                maxfd = fd;
            }

            FD_SET(fd, &read_fds); //添加描述符, we monitor first two fds for reading
            // FD_SET(fd, &write_fds);
        }
 
        maxfd++; //描述符最大值加1
        // int select(int maxfdp,fd_set *readfds,fd_set *writefds,fd_set *errorfds,struct timeval *timeout)
        // （1）int maxfdp是一个整数值，是指集合中所有文件描述符的范围，即所有文件描述符的最大值加1，不能错。
        // 说明：对于这个原理的解释可以看上边fd_set的详细解释，fd_set是以位图的形式来存储这些文件描述符。maxfdp也就是定义了位图中有效的位的个数。
        // （2）fd_set *readfds是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的读变化的，即我们关心是否可以从这些文件中读取数据了，
        //     >0: 如果这个集合中有一个文件可读，select就会返回一个大于0的值，表示有文件可读；
        //     =0: 如果没有可读的文件，则根据timeout参数再判断是否超时，若超出timeout的时间，select返回0，
        //     <0: 若发生错误返回负值.
        //     可以传入NULL值，表示不关心任何文件的读变化。
        // （3）fd_set *writefds是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的写变化的，即我们关心是否可以向这些文件中写入数据了，
        //     >0: 如果这个集合中有一个文件可写，select就会返回一个大于0的值，表示有文件可写，
        //     =0: 如果没有可写的文件，则根据timeout参数再判断是否超时，若超出timeout的时间，select返回0，
        //     <0: 若发生错误返回负值。
        //      可以传入NULL值，表示不关心任何文件的写变化。
        // （4）fd_set *errorfds同上面两个参数的意图，用来监视文件错误异常文件。
        // （5）struct timeval* timeout是select的超时时间，这个参数至关重要，它可以使select处于三种状态，
        //      第一，若将NULL以形参传入，即不传入时间结构，就是将select置于阻塞状态，一定等到监视文件描述符集合中某个文件描述符发生变化为止；
        //      第二，若将时间值设为0秒0毫秒，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化，都立刻返回继续执行，文件无变化返回0，有变化返回一个正值；
        //      第三，timeout的值大于0，这就是等待的超时时间，即 select在timeout时间内阻塞，超时时间之内有事件到来就返回了，否则在超时后不管怎样一定返回，返回值同上述。
        switch(select(maxfd, &read_fds, NULL/* &write_fds */, NULL, NULL/* &timeout */)) {
        case -1:
            exit(-1);   //select错误，退出程序  
            break; 
        case 0:
            break; //再次轮询 
        default:  
            {
                for (int i=0; i < g_connect_fds.size(); i++) {
                    int fd = g_connect_fds[i];
                    if(FD_ISSET(fd, &read_fds)) { //测试sock是否可读，即是否网络上有数据
                        read(fd, buffer, 256);
                        std::cout << "fd " << fd << " is readable, msg:" << buffer << std::endl;
                    } 
                }
            }
            break;
        }
    }
}

void init_net()
{
    std::cout << "This is server" << std::endl;

    unsigned short port = 7890;
    const char* ip = "127.0.0.1";

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == fd) {
        std::cout << "Socket failed" << std::endl;
        exit(-1);
    }
    g_fd = fd;

    struct sockaddr_in s_add, c_add;
    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = htonl(INADDR_ANY);
    s_add.sin_port = htons(port);

    if(-1 == bind(fd, (struct sockaddr *)(&s_add), sizeof(struct sockaddr))) {
        printf("bind failed !\n");
        exit(-1);
    }

    if(-1 == listen(fd, 50)) {
        printf("listen failed !\n");
        exit(-1);
    }
    printf("listen ok\n");

    socklen_t sin_size = sizeof(struct sockaddr);
    for (int i = 0; i < MAX_CONNECTIONS; i++) {
        int l_fd = accept(fd, (struct sockaddr *)(&c_add), &sin_size);
        if(-1 == l_fd) {
            printf("accept fail !\n");
            exit(-1);
        }
        printf("accept ok!\nServer start get connect from %s : %d\n", inet_ntoa(c_add.sin_addr), ntohs(c_add.sin_port));
        g_connect_fds.push_back(l_fd);
    }
}
