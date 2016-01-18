#include <iostream>
#include <cstring>

class A
{
public:
    A(const char* s): data(nullptr), len(0) {
        std::cout << "Default A is invoked" << std::endl;
        len = strlen(s);
        data = new char[len + 1];
        memcpy(data, s, len);
        data[len] = '0';
    }
    // A(const A& a) {
    //     std::cout << "Default A(&) is invoked" << std::endl;
    //     len = a.len;
    //     data = new char[a.len + 1];
    //     memcpy(data, a.data, a.len);
    //     data[len] = '0';
    // }

    // A(A&& a) {
    //     std::cout << "Default A(&&) is invoked" << std::endl;
    //     len = a.len;
    //     data = a.data;
    //     a.len = 0;
    //     a.data = nullptr;
    // }
    ~A() {
        std::cout << "Defuult ~A is invoked" << std::endl;
        // delete
    }

    A& operator=(const char* s) {
        std::cout << "Defuult operator=(const char*) is invoked" << std::endl;
        delete(data);
        len = strlen(s);
        data = new char[len + 1];
        memcpy(data, s, len);
        data[len] = '0';
        return *this;
    }

    A& operator=(const A& a) {
        std::cout << "Defuult operator=(A&) is invoked" << std::endl;
        if (len != a.len) {
            delete(data);
        }
        len = a.len;
        data = new char[len + 1];
        memcpy(data, a.data, len);
        return *this;
    }

    // A& operator=(A&& a) {
    //     std::cout << "Defuult operator=(A&&) is invoked" << std::endl;
    //     char* p = data;
    //     int tmp = len;
    //     data = a.data;
    //     len = a.len;
    //     a.data = p;
    //     a.len = tmp;
    //     return *this;
    // }

private:
    char* data;
    int len;
};


int main(int argc, char** argv) {
    std::string a("aaaaa");
    std::string b = std::move(a);
    std::cout << "b [" << b << "], a [" << a  << "]" << std::endl;
    // a, b swap
    std::string c("cccc");
    c = std::move(b);
    // b, c swap, so
    std::cout << "b [" << b << "], a [" << a  << "], c [" << c << "]" << std::endl;



    // 1.如果类没有自定义的拷贝构造,编译器会自动生成一个.这时候,如果定义了一个赋值拷贝构造,那么,编译器会不会生成拷贝构造,而且会把拷贝构造设置成delete.因为会使含义不清. 
    //     A a = "aaa";
    //     A b = a; // 使用默认拷贝构造, 但是delete了,出错了. 

    // note: ‘constexpr A::A(const A&)’ is implicitly declared as deleted because ‘A’ declares a move constructor or move assignment operator
    //  class A


    // 但是, 如果你自己定义了一个拷贝构造,再定义一个赋值拷贝构造,那么,就不会有问题.这就像std::string 一样.
    //    std::string a("aaaa")
    //    std::string b = a; // 这个会调用string的构造函数的 string(const string&)
    //    同时,string肯定显示的声明了string(const string& )构造函数,并且也显示的声明了 string(string&&)赋值构造函数.

    {
        std::cout << "----------------------\n";
        A a1("this is a");
        A a2 = a1;
    }

    {
        std::cout << "----------------------\n";
        A b1("This is b");
        A b2 = std::move(b1);
    }
}