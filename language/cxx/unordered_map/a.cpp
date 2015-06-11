#include <iostream>
#include <unordered_map>



int main() {

    std::unordered_map<std::string, std::string> map;
    auto ret = map.insert(std::make_pair<std::string, std::string>("aa", "bb"));

    auto it = ret.first;
    std::cout << (ret.second ? "true" : "false") << ", key:" <<it->first
            << ", value:" << it->second << std::endl;

    ret = map.emplace("cc", "bb");
    it = ret.first;
    std::cout << (ret.second ? "true" : "false") << ", key:" <<it->first
            << ", value:" << it->second << std::endl;

}