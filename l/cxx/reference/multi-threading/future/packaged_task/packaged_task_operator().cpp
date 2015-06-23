#include <future>
#include <iostream>
#include <thread>



int simple_task(int i) { return i*3; }

int main() {
    std::packaged_task<int(int)> task(simple_task);

    std::future<int> fut = task.get_future();

    try {
        task(10); // why ???? got exception ?? but if we reset and use it in another thread, it will be ok again. see reset.cpp
    } catch (std::exception& e) {
        std::cout << "exception caught: " << e.what() << std::endl;
        return 0;
    }

    std::cout << "Triple 10 is " << fut.get() << std::endl;
}