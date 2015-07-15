#include <iostream>
#include <unordered_map>
#include <vector>


int main() {
    std::unordered_map<int, std::vector<int>> a_map;
    auto& v = a_map[10];
    if (v.empty()) {
        // v.push_back(11);
    }

    auto it = a_map.find(10);
    if (it != a_map.end()) {
        if (it->second.size() > 0) {
            const auto& first_value = it->second.at(0);
            std::cout << "10 is in, value[0] is " <<  first_value << std::endl;
        } else {
            std::cout << "10 is in but got value" << std::endl;
        }
    } else {
        std::cout << "10 is NOT in " << std::endl;
    }
}