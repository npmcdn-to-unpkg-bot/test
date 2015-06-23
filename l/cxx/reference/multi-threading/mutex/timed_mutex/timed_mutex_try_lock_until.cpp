// timed_mutex::try_lock_until example
#include <iostream>       // std::cout
#include <chrono>         // std::chrono::system_clock
#include <thread>         // std::thread
#include <mutex>          // std::timed_mutex
#include <ctime>          // std::time_t, std::tm, std::localtime, std::mktime

std::timed_mutex cinderella;

// gets time_point for next midnight:
std::chrono::time_point<std::chrono::system_clock> midnight() {
  using std::chrono::system_clock;
  std::time_t tt = system_clock::to_time_t (system_clock::now());
  struct std::tm * ptm = std::localtime(&tt);
  ptm->tm_sec += 10; // delay 10 seconds
  return system_clock::from_time_t (mktime(ptm));
}

void carriage() {
  std::this_thread::sleep_for(std::chrono::seconds(1)); // let ball get the lock first

  if (cinderella.try_lock_until(midnight())) {
    std::cout << "get the lock\n";
    cinderella.unlock();
  }
  else
    std::cout << "didn't get the lock\n";
}

void ball() {
  cinderella.lock();
  std::cout << "at the ball...\n";
  std::this_thread::sleep_for(std::chrono::seconds(11));
  cinderella.unlock();
}

int main ()
{
  std::thread th1 (ball);
  std::thread th2 (carriage);

  th1.join();
  th2.join();

  return 0;
}