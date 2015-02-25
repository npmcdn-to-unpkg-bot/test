#include <iostream>

class A {
public:
    enum Result {
        success,
        failed
    };

    virtual Result send() = 0;
};

class B : public A {
public:
    Result send() { return failed; }
};

int main() {

    B b;
    auto r = b.send();
    if (r == A::success)
        std::cout << "return success\n";
    else
        std::cout << "return failed\n";
}