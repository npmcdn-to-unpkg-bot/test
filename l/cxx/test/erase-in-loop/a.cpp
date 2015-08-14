#include <unordered_map>
#include <iostream>



std::unordered_map<int, int> a_map;

void print_map() {
    for (const auto& entry : a_map) {
        std::cout << entry.first << ":" << entry.second << std::endl;
    }
    std::cout << "-----------------------------------\n";

}

int main() {
    for (int i=0; i<5; i++) {
        a_map[i] = i;
    }
    print_map();

    // a good way, if you want to erase in a loop
    for (auto it = a_map.begin(); it != a_map.end(); ) {
        if (it->second == 2) {
            it = a_map.erase(it);
        } else {
            it++;
        }
    }
    print_map();

    // This should crash, but this time it didn't.
    // but you'll see it print something you don't want
    for (auto it = a_map.begin(); it != a_map.end(); it++) {
        std::cout << it->first << "," << it->second << std::endl;
        if (it->second == 3) {
            a_map.erase(it);
        }
    }
    // print_map();
}
