#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <errno.h>

int main() {

    time_t rv_seconds;
    time_t seconds = time(&rv_seconds);
    assert(rv_seconds == seconds); // the same, you can use time(NULL);
    std::cout << "seconds=" << rv_seconds << std::endl;

    struct  timeval    tv;
    struct  timezone   tz;
    int i = gettimeofday(&tv, &tz);
    if (i != 0) {
        std::cout << "failed to gettimeofday, error:" << strerror(errno) << std::endl;
        return 0;
    }

    std::cout << "tv_sec:" << tv.tv_sec << ", tv_usec:" << tv.tv_usec << std::endl;
    std::cout << "tz_minuteswest:" << tz.tz_minuteswest << ", tz_dsttime:" << tz.tz_dsttime << std::endl;

    i = gettimeofday(&tv, NULL); // You can put NULL into parameter.
    if (i != 0) {
        std::cout << "failed to gettimeofday, error:" << strerror(errno) << std::endl;
        return 0;
    }
    std::cout << "tv_sec:" << tv.tv_sec << ", tv_usec:" << tv.tv_usec << std::endl;

}