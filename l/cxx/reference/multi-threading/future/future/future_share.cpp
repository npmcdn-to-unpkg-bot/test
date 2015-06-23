#include <iostream>
#include <future>

/*

shared_future<T> share();
^^^^^^^^^^^^^

Get shared future
Returns a shared_future object that acquires the shared state of the future object.
           ^^^^^^^^^^^
The future object (*this) is left with no shared state (as if default-constructed) and is no longer valid.


*/


int echo_value(int i) { return i; }


int main() {
    std::future<int> foo = std::async(echo_value, 11);
    std::shared_future<int> bar = foo.share(); // move-assign, foo is not valid anymore.
    //    ^^^^^^^^^^^^
    if (!foo.valid()) {
        std::cout << "foo is not valid anymore" << std::endl;
    } else {
        std::cout << "foo is still valid" << std::endl;
    }

    std::cout << "bar is " << bar.get() << std::endl;
}