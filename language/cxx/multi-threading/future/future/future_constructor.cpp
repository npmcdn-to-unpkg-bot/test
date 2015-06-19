#include <future>
#include <iostream>

int get_value() { return 10; }
int echo_value(int i) { return i; }

int main() {
    std::future<int> foo;
    std::future<int> bar = std::async(get_value);
    std::future<int> coo = std::async(echo_value, 11);

    if (!foo.valid()) {
        std::cout << "foo is not valid" << std::endl;
    } else {
        std::cout << "foo is valid" << std::endl;
    }

    try { // foo is not valid, if we still get(), an exception will be caught.
        foo.get();
    } catch (std::exception& e) {
        std::cout << "exception caught: " << e.what() << std::endl;
    }

    std::cout << "bar get value:" << bar.get() << std::endl;
    std::cout << "coo get value:" << coo.get() << std::endl;
}