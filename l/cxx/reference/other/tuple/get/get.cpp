// tuple's get
#include <iostream>
#include <tuple>

class A {
public:
    A() {
        static int c = 0;
        i_ = c;
        c++;
    }
    void p() { std::cout << "this is A:" << i_ << std::endl; }
private:
    int i_;
};


class B {
public:
    B() {
        static int c = 0;
        i_ = c;
        c++;
    }
    void p() { std::cout << "this is B:" << i_ << std::endl; }
private:
    int i_;
};


int main ()
{
  std::tuple<int,char, long> mytuple (10,'a', 11);

  std::get<0>(mytuple) = 20;

  std::cout << "mytuple contains: ";
  std::cout << std::get<0>(mytuple) << ", " << std::get<1>(mytuple) << ", " << std::get<2>(mytuple);
  std::cout << std::endl << std::endl;


  std::tuple<int, A, A*, B> mytuple1(10, A(), new A(), B());
  std::cout << "mytuple1 contains: ";
  std::cout << std::get<0>(mytuple1) << std::endl;
    std::get<1>(mytuple1).p();
    std::get<2>(mytuple1)->p();
    std::get<3>(mytuple1).p();
  std::cout << std::endl;

  return 0;
}