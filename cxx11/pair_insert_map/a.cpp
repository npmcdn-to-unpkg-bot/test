#include <unordered_map>
#include <map>
#include <iostream>



int main() {

    std::unordered_map<std::pair<int, int>, int > a;
    auto entry = std::make_pair<int, int>(3, 4);
    a[entry] = 1;

    auto it = a.find(entry);
    std::cout << it->first.first << "," << it->first.second << "," << it->second
            << std::endl;

}