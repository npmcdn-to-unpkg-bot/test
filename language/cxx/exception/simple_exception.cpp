#include <iostream>



int main() {
    try {
        // throw 20;
        throw 'a';
        throw 2.0;
    }
    catch (int e) {
        std::cout << "exception int " << e << std::endl;
    }
    catch (char e) {
        std::cout << "exception char " << e << std::endl;
    }
    catch (...) {
        std::cout << "exception default " << std::endl;
    }
}