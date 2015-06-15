#include <thread>
#include <iostream>
#include <chrono>

/*
std::this_thread::sleep_for
template <class Rep, class Period> void sleep_for (const chrono::duration<Rep,Period>& rel_time);

Sleep for time span
Blocks execution of the calling thread during the span of time specified by rel_time.

The execution of the current thread is stopped until at least rel_time has passed from now. Other threads continue their execution.
*/


// g++ xxx.cpp --std=c++11 -lpthread


int main() {
    std::cout << "countdown\n";
    for (int i=0; i< 10; i++) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    std::cout << "Lift off\n";
    return 0;
}