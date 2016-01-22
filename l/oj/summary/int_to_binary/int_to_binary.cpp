#include <iostream>
#include <vector>

void int_to_binary(unsigned n, std::vector<int>& result) {
    while (n != 0) {
        int r = n%2;
        n = (n - r)/2;
        result.push_back(r);
    }
}

void print_binary(const std::vector<int>& v) {
    for (int i=v.size() - 1; i>=0; i--) {
        std::cout << v[i];
    }
    std::cout << std::endl;
}

int main(int argc, char** argv) {

    std::vector<int> v;
    int_to_binary(6, v);
    print_binary(v);

    v.clear();
    int_to_binary(7, v);
    print_binary(v);

    v.clear();
    int_to_binary(8, v);
    print_binary(v);
}