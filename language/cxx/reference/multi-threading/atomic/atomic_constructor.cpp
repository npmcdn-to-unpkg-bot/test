#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <chrono>

/*

Data races
The construction itself is not atomic: Accessing the object while being constructed may initiate a data race.

*/

std::atomic<bool> ready(false);
std::atomic_flag winner = ATOMIC_FLAG_INIT;

void count1m(int id) {
    while(!ready) {
        // std::cout << "Thread #" << id << "yield\n";
        std::this_thread::yield();
    }

    for (volatile int i=0; i<1000000; ++i) {

    }

    if (!winner.test_and_set()) {
        std::cout << "thread #" << id << " won!\n";
    }
}

int main() {
    std::vector<std::thread> threads;
    std::cout << "Spawning 10 threads that count to 1 million...\n";
    for (int i=0; i<10; i++) {
        threads.push_back(std::thread(count1m, i));
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));
    ready = true;
    for (auto& th : threads) th.join();

    return 0;
}
