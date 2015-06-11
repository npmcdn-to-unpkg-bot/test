#include <unordered_map>
#include <unordered_set>
#include <iostream>



int main() {
    std::unordered_set<std::string> set;
    set.insert("aa");
    set.insert("bb");

    for (auto it : set) {
        std::cout << "key:" << it << std::endl;
    }
}

// set for() it is the value.
// key:bb
// key:aa
