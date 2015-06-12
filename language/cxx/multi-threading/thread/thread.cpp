#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

// g++ thread.cpp --std=c++11 -lpthread


std::atomic<int> global_counter(0);

void increase_global(int n) {
    for (int i=0; i<n; ++i) {
        ++global_counter;
    }
}

void increase_reference(std::atomic<int>& variable, int n) {
    for (int i=0; i<n; ++i) {
        ++variable;
    }
}

struct C : std::atomic<int>
{
    C() : std::atomic<int>(0) {}
    void increase_member(int n) {
        for (int i=0; i<n; ++i) {
            fetch_add(1);
        }
    }
};

void thread1() {
    std::cout << "This is thread1" << std::endl;
}

void thread2(int arg1, const std::string& arg2) {
    std::cout << "this is thread2, arg1 "<< arg1 << ", arg2 " << arg2 << std::endl;
}

int main() {

    // Part One
    std::thread t1(thread1);
    std::thread t2(thread2, 10, "wahaha");

    std::cout << "main, thread1, thread2 now execute concurrently\n";

    t1.join();
    t2.join();
    std::cout << "thread1, thread2 now completed\n";

    // Part two
    std::vector<std::thread> threads;

    std::cout << "increase global counter with 10 threads...\n";
    for (int i=1; i<=10; ++i)
        threads.push_back(std::thread(increase_global,1000));

    std::cout << "increase counter (foo) with 10 threads using reference...\n";
    std::atomic<int> foo(0);
    for (int i=1; i<=10; ++i)
        threads.push_back(std::thread(increase_reference,std::ref(foo),1000));

    std::cout << "increase counter (bar) with 10 threads using member...\n";
    C bar;
    for (int i=1; i<=10; ++i)
        threads.push_back(std::thread(&C::increase_member, &bar,1000));
    //  threads.push_back(std::thread(&C::increase_member, std::ref(bar),1000));
    // see http://bbs.csdn.net/topics/390800501
    // C++11的std::thread构造函数不支持std::ref的这种用法。
    // 你可以认为这是C++11标准的一个缺陷（LWG #2219）。不幸的是GCC 4.8很积极地迎合了标准。
    // 目前，你可以用传指针的方式

    std::cout << "synchronizing all threads...\n";
    for (auto& th : threads) th.join();

    std::cout << "global_counter: " << global_counter << '\n';
    std::cout << "foo: " << foo << '\n';
    std::cout << "bar: " << bar << '\n';

    return 0;
}