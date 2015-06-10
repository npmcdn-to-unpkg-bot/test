#include <iostream>



int main() {
    try {
        throw 20;
    } catch (int e) {
        std::cout << "exception " << e << std::endl;
    }
}