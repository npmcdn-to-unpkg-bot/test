#include <iostream>
#include <cstring>

// strtok会把第一个参数给拆分掉,所以你原来的输入就没拉!!

int main(int argc, char** argv) {
    char s[] = "This. is a#special# !string";
    char d[] = " .#!";

    char* p = strtok(s, d);
    while (p) {
        std::cout << p << std::endl;
        p = strtok(nullptr, d);
    }
    std::cout << "------------------" << std::endl;
    std::cout << s << std::endl;

}