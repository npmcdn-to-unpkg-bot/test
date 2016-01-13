#include <iostream>

int main(int argc, char** argv) {
    std::string str ("There are two needles in this haystack with needles.");
    //                012345678901234
    std::string str2 ("needle");

    // different member versions of find in the same order as above:
    std::size_t found = str.find(str2);
    if (found!=std::string::npos)
        std::cout << "first 'needle' found at: " << found << '\n'; // 14

    found = str.find("There");
    if (found != std::string::npos)
        std::cout << "There found at: " << found << std::endl; // 0, the same as the index of array

    found=str.find("needles are small",found+1,6);
    if (found!=std::string::npos)
        std::cout << "second 'needle' found at: " << found << '\n';

    found=str.find("haystack");
    if (found!=std::string::npos)
        std::cout << "'haystack' also found at: " << found << '\n';

    found=str.find('.');
    if (found!=std::string::npos)
        std::cout << "Period found at: " << found << '\n';

    // let's replace the first needle:
    str.replace(str.find(str2),str2.length(),"preposition");
    std::cout << str << '\n';


    return 0;
}