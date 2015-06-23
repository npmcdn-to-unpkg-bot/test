#include <thread>
#include <chrono>
#include <iomanip> // std::put_time
#include <ctime> // std::time_t, std::tm, std::local_time, std::mktime
#include <iostream>

/*
std::this_thread::sleep_until

template <class Clock, class Duration>
  void sleep_until (const chrono::time_point<Clock,Duration>& abs_time);

Sleep until time point
Blocks the calling thread until abs_time.

The execution of the current thread is stopped until at least abs_time, while other threads may continue to advance.

Parameters
    -abs_time
        A point in time when the calling thread shall resume its execution.
        Note that multi-threading management operations may cause certain delays beyond this.
        time_point is an object that represents a specific absolute time.
*/


// g++ xx.cpp --std=c++11 -lpthread


int main() {
    std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    struct std::tm* ptm = std::localtime(&tt);
    // std::put_time is missing in 4.9 but avaible in 5.x
    // std::cout << "Current time:" << std::put_time(ptm, "%X") << std::endl;
    std::cout << "Current time, min:" << ptm->tm_min << ", seconds:" << ptm->tm_sec << std::endl;
    std::cout << "Waiting for the next minite to begin\n";
    ++ptm->tm_min;
    ptm->tm_sec = 0;
    std::this_thread::sleep_until(std::chrono::system_clock::from_time_t(mktime(ptm)));

    // std::cout << std::put_time(ptm, "%X") << "reached\n";
    std::cout << "Current time, min:" << ptm->tm_min << ", seconds:" << ptm->tm_sec << std::endl;

    return 0;
}


