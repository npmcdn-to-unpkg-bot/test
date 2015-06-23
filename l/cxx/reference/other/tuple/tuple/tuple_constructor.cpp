#include <iostream>
#include <tuple>
#include <utility>

int main() {
    std::tuple<int, char> first; // default
    std::tuple<int, char> second(first); // copy
    std::tuple<int, char> third(std::make_tuple(20, 'b')); // move
    std::tuple<long, char> fourth(third); // implicit conversion
    std::tuple<int, char> fifth(10, 'a'); // initialization
    std::tuple<int, char> sixth(std::make_pair(30, 'c')); // from pair/ move

    std::cout << "sixth contains:" << std::get<0>(sixth)
        << " and " << std::get<1>(sixth) << std::endl;
}