#include <iostream>


// If non-int is throw, core dump, call  std::unexpected
// If int is thrown, looking for handler or call std:terminate
double my_func() throw(int) {
    std::cout << "this is my function" << std::endl;
    throw('1'); // We still can throw a char type exception, but this will core dump, won't be caught.
    throw(10); 
}

// All type is considered as std::unexpected. core dump.
double throw_all() throw() { // all exceptions call unexpected
    std::cout << "this is my function" << std::endl;
    throw("all");
}

int myfunction (int param)  // normal exception handling
{

}

int main() {
    try {
        my_func();
    }
    catch (char e) {
        std::cout << "exception " << e << std::endl;
    }
    // catch (...) {
    //     std::cout << "default exception" << std::endl;
    // }

    my_func(); // If we don't catch, it will core dump.

    throw_all();
}