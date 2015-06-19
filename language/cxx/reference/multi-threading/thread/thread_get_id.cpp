#include <thread>
#include <iostream>
#include <chrono>


//  g++ thread_get_id.cpp --std=c++11 -lpthread


std::thread::id main_thread_id = std::this_thread::get_id();

void is_main_thread() {
    if (main_thread_id == std::this_thread::get_id()) {
        std::cout << "This is main thread\n";
    } else {
        std::cout << "this is not the main thread\n";
    }
}

int main() {
    is_main_thread();

    std::thread th(is_main_thread);
    th.join();
}