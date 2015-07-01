#include <chrono>
#include <iostream>




int main() {
    std::chrono::milliseconds foo(1000);
    foo *= 1000;
    // foo += 33; // no implicit conversion
    foo += std::chrono::milliseconds(33333);

    std::cout << "duration (in periods):" << foo.count() << " milliseconds" << std::endl;
    std::cout << "duration (in seconds):"
            << foo.count() * std::chrono::milliseconds::period::num / std::chrono::milliseconds::period::den
            << " seconds" << std::endl;

}