#include <iostream>
#include <thread>
#include <future>

int simple_task(int i) {return 3*i;}

int main() {
    std::packaged_task<int(int)> task(simple_task);
    std::future<int> fut = task.get_future();
    task(33);
    std::cout << "triple 33 is " << fut.get() << std::endl;
    // std::cout << "triple 33 is " << fut.get() << std::endl; // call it again will core dump because of No associated state

    task.reset();
    fut = task.get_future();
    std::thread(std::move(task), 22).detach();
    std::cout << "Triple 22 is " << fut.get() << std::endl;

}