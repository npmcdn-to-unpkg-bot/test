#include <future>
#include <iostream>
#include <thread>

int simple_task(int i) { return i*3; }

int main() {

    std::packaged_task<int(int)> task(simple_task);
    auto fut = task.get_future();

    std::thread(std::move(task), 33).detach();

    std::cout << "triple 33 is " << fut.get() << std::endl;

}