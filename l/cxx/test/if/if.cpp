#include <iostream>


void print_if(int v) {
    if (v) {
        std::cout << "If (" << v  << ") means true" << std::endl; 
    } else {
        std::cout << "If (" << v << ") means false" << std::endl;
    }
}

int main() {
    print_if(-1);
    print_if(0);
    print_if(1);
}
