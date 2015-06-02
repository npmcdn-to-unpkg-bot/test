#include <memory>
#include <iostream>



class A {
public:
    A() {
        std::cout << "A is created:" << this << std::endl;
    }
    ~A() {
        std::cout << "A is destroyed:" << this << std::endl;
    }
};

class B {
public:
    B() {
        std::cout << "B is created:" << this << std::endl;
        m_a.reset(new A);
    }
    ~B() {
        std::cout << "B is destroyed:" << this << std::endl;
    }
    std::shared_ptr<A> m_a;
};



int main() {
    B b;
    B bb = b;
    std::cout << "a in b:" << b.m_a.get() << std::endl;
    std::cout << "a in bb:" << bb.m_a.get() << std::endl;

}
