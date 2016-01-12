#include <iostream>


int main(int argc, char** argv) {
    char* p = new char(4);
    int* p0 = new int(4);

    char p1[] = { '1', '2', '3', '4' };
    int p2[] = { 1, 2, 3, 4 };
    int* p3 = p2;
    std::cout << "sizeof char  : " << sizeof('a') << std::endl;
    std::cout << "sizeof short : " << sizeof(short(4)) << std::endl;
    std::cout << "sizeof int   : " << sizeof(int(4)) << std::endl;
    std::cout << "sizeof long  : " << sizeof(long(4)) << std::endl;
    std::cout << "sizeof double: " << sizeof(double(4)) << std::endl;
    std::cout << "sizeof float : " << sizeof(float(4)) << std::endl;
    std::cout << "sizeof size_t: " << sizeof(size_t(4)) << std::endl;
    std::cout << "sizeof pointer char* p = new char(4): " << sizeof(p) << std::endl;
    std::cout << "sizeof pointer int* p0 = new int(4) : " << sizeof(p0) << std::endl;
    // int[]  sizeof is the real length.
    std::cout << "sizeof char p1[] = { '1', '2', '3', '4' }: " << sizeof(p1) << std::endl;
    std::cout << "sizeof int p2[] = { 1, 2, 3, 4 }: " << sizeof(p2) << std::endl;
    std::cout << "sizeof int* p3 = p2: " << sizeof(p3) << std::endl; // this is a pointer

}