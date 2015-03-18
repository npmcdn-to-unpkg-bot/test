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