#include <iostream>

// const char* == char const*


int fun1(const char* msg) {
    const char t[] = "new string fun1";
    msg = t;
    // *msg = "new string fun1"; // error: assignment of read-only location ‘* msg’ *msg = "new string fun1";
    std::cout << "fun 1 msg:" << msg << std::endl;
}


int fun2(char const* msg) {
    char t[] = "new string fun2";
    msg = t;
    // *msg = "new string fun222222";
    std::cout << "fun 2 msg:" << msg << std::endl;
}

int main() {
    fun1("dafei fun1");
    fun2("dafei fun2");
}