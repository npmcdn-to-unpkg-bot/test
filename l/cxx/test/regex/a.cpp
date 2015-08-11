#include <string>
#include <regex>
#include <iostream>

// g++ a.cpp --std=c++11

std::string get_str() {
    std::string a_string = "a=mid:0 audio\n";
    a_string += "a=candidate: aaaaaaaa\n";
    a_string += "a=end-of-candidates";
    return a_string;
}

int main() {
    std::string sdp = get_str();


    std::regex re_aline("a=([^:]+):([^\r\n]+)");
    std::regex_iterator<std::string::const_iterator> re_it(sdp.begin(), sdp.end(),
            re_aline);
    const std::regex_iterator<std::string::const_iterator> re_end;

    int mline_index = 0;
    std::string mid;
    std::string body;

    while(re_it != re_end) {
        std::smatch match = *re_it;
        std::string field = match[1];
        std::string value = match[2];
        if (field == "mid") {
            std::istringstream ios(value);
            ios >> mline_index >> mid;
        } else if (field == "candidate") {
            body = field+":"+value;
        } else if (field == "end-of-candidate") {
            //nothing to do
        }
        ++re_it;
    }

    std::cout << "index:" << mline_index <<", mid:" << mid << ", candidate:" <<  body << std::endl;
}