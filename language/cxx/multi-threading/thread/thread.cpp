#include <iostream>
#include <thread>

// g++ thread.cpp --std=c++11 -lpthread

void thread1() {
    std::cout << "This is thread1" << std::endl;
}

void thread2(int arg1, const std::string& arg2) {
    std::cout << "this is thread2, arg1 "<< arg1 << ", arg2 " << arg2 << std::endl;
}

int main() {

    std::thread t1(thread1);
    std::thread t2(thread2, 10, "wahaha");

    std::cout << "main, thread1, thread2 now execute concurrently\n";

    t1.join();
    t2.join();
    std::cout << "thread1, thread2 now completed\n";
    return 0;
}