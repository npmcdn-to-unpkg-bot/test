#include <iostream>
#include <future>

int echo_value(int i) { return i; }

int main() {
    std::future<int> foo; // default future, invalid
    foo = std::async(echo_value, 11); // move-assign
    std::cout << "11 echo is " << foo.get() << std::endl;
}