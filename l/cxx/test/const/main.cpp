#include <iostream>

class A {
public:
    void print() {
        std::cout << "print non-const\n";
    }

    void print() const {
        std::cout << "print const\n";
        // a = 1;
    }

public:
    int a;
};


void t_const(const A& a) {
    a.print();
}

void t_nonconst(A& a) {
    a.print();
}

int main() {

    A a;
    t_const(a);
    t_nonconst(a);
}