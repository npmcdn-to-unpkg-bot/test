#include <iostream>
#include <sstream>
#include <vector>

// Go to refrence/c-libary/cstring to use strtok to split a char* with delimiter.

// use sstream to split a string with " " or "\n"
std::vector<std::string> split(const std::string& s) {
    std::istringstream stream(s);
    std::vector<std::string> v;
    std::string tmp;
    while (stream >> tmp) {
        v.push_back(tmp);
    }
    return v;
}

// use string::find() to split a string with delimiter
std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> v;
    if (s.empty()){
        return v;
    }
    if (delimiter.empty()) {
        v.push_back(s);
        return v;
    }

    size_t start = 0;
    while(true) {
        auto pos = s.find(delimiter, start);
        // std::cout << "start:" << start << ", pos:" << pos << std::endl;
        if (pos == std::string::npos) {
            // std::cout << "push in:" << s.substr(start) << std::endl;
            v.push_back(s.substr(start));
            break;
        }

        if (pos != start) {
            // std::cout << "push in:" << s.substr(start, pos - start) << std::endl;
            v.push_back(s.substr(start, pos - start));
        }
        start = pos + 1;
    }
    return v;
}

int main(int argc, char** argv) {
    std::string s("This is a string\nyou know ?");

    auto v = split(s);
    for (const auto& entry : v) {
        std::cout << entry << std::endl;
    }

    std::cout << "-------------------------\n";
    std::string s1("This##is#a#special###string!!");
    //              01234567890123456789012345678
    auto v1= split(s1, "#");
    for (const auto& entry : v1) {
        std::cout << entry << std::endl;
    }
}
