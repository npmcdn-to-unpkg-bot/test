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


int main(int argc, char** argv) {
    int fds[2];
    char buf[256] = { 0 };
    // 1) 头文件 #include<unistd.h>
    // 2) 定义函数： int pipe(int filedes[2]);
    // 3) 函数说明： pipe()会建立管道，并将文件描述词由参数filedes数组返回。
    //               filedes[0]为管道里的读取端
    //               filedes[1]则为管道的写入端。
    // 4) 返回值：  若成功则返回零，否则返回-1，错误原因存于errno中。
    //     错误代码: 
    //          EMFILE 进程已用完文件描述词最大量
    //          ENFILE 系统已无文件描述词可用。
    //          EFAULT 参数 filedes 数组地址不合法。

    int ret = pipe(fds);
    if (ret != 0) {
        std::cout << "pipe failed\n";
        exit(-1);
    }

    sprintf(buf, "Hello, pipe");
    ret = write(fds[1], buf, strlen(buf) + 1);
    if (ret <= 0) {
        std::cout << "write failed:" << strerror(errno) << std::endl; // 0 means write nothing.
        exit(-1);
    }

    memset(buf, 256, 0);
    int len = read(fds[0], buf, 256);
    if (len <= 0) {
        std::cout << "read failed" << std::endl;
        exit(-1);
    }
    std::cout << "read msg:" << buf << std::endl;

    return 0;
}