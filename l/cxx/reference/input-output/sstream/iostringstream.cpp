#include <sstream>
#include <iostream>

int main(int argc, char** argv) {
    // istringstream.str()
    // ostringstream.str()

    // istringstream for read string with ' ' and '\n'
    std::istringstream stream("this is unacceptable !\n Fuck\n");
    std::string tmp;
    while(stream >> tmp) {
        std::cout << tmp << std::endl;
    }

    // ostringstream for formatting output
    std::ostringstream format_stream;
    std::string s("a string");
    int i = 10;
    format_stream << "This is " << s << " and int " << i;
    std::cout << format_stream.str() << std::endl;
}