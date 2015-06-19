#include <iostream>
#include <thread>
#include <future>

/*

void reset();
Reset task
Resets the object with a new shared state while keeping the same stored task.

This allows the stored task to be called again.

The shared state associated to the object before the call (if any) is abandoned (as if the packaged_task was destroyed).

Internally, the function behaves as if move-assigned a newly constructed packaged_task (with its stored task as argument).


*/


int simple_task(int i) {return 3*i;}

int main() {
    std::packaged_task<int(int)> task(simple_task);
    std::future<int> fut = task.get_future();
    task(33);
    std::cout << "triple 33 is " << fut.get() << std::endl;
    // std::cout << "triple 33 is " << fut.get() << std::endl; // call it again will core dump because of No associated state

    // re-use same task object:
    task.reset();
    fut = task.get_future();
    std::thread(std::move(task), 22).detach();
    std::cout << "Triple 22 is " << fut.get() << std::endl;
    return 0;
}