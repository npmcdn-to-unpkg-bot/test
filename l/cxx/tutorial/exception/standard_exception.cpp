#include <exception>
#include <iostream>


// virtual const char* what() const throw(); // override it.

class myException : public std::exception {
public:
    virtual const char* what() const throw() override {
        return "My exception";
    }
};

int main() {
    try {
        throw myException();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}