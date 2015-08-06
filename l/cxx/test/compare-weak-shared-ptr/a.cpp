#include <memory>
#include <iostream>
#include <vector>

class A {
public:
    void p() {}
private:
   int   m_id;
};


int main() {
    std::shared_ptr<A> shared = std::make_shared<A>();
    std::weak_ptr<A> weak = shared;

    // can't just shared == weak.
    if (shared == weak.lock()) {
        std::cout << "shared == weak" << std::endl;
    } else {
        std::cout << "shared != weak" << std::endl;
    }

    std::vector<std::weak_ptr<A>> array;
    array.push_back(weak);

    // can't compile
    // auto it = std::find(array.begin(), array.end(), weak);
    // if (it != array.end()) {
    //     std::cout << "Found shared in weak vector" << std::endl;
    // }

    auto it = array.begin();
    for (; it != array.end(); it++) {
        auto s = it->lock();
        if (s == shared) {
            std::cout << "Found shared in vector" << std::endl;
            break;
        }
    }
    array.erase(it);
    std::cout << "After erase, vector size:" << array.size() << std::endl;
}