// lock_guard example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::lock_guard
#include <stdexcept>      // std::logic_error

/*

Lock guard
A lock guard is an object that manages a mutex object by keeping it always locked.

On construction, the mutex object is locked by the calling thread, and on destruction, 
the mutex is unlocked. It is the simplest lock, and is specially useful as an object with 
automatic duration that lasts until the end of its context. In this way, it guarantees 
the mutex object is properly unlocked in case an exception is thrown.

Note though that the lock_guard object does not manage the lifetime of the mutex object in any way:
 the duration of the mutex object shall extend at least until the destruction of the lock_guard that locks it.

*/


std::mutex mtx;

void print_even (int x) {
  if (x%2==0) std::cout << x << " is even\n";
  else throw (std::logic_error(" is not even"));
}

void print_thread_id (int id) {
  try {
    // using a local lock_guard to lock mtx guarantees unlocking on destruction / exception:
    std::lock_guard<std::mutex> lck (mtx);
    print_even(id);
  }
  catch (std::logic_error& e) {
    std::lock_guard<std::mutex> lck(mtx); // protect std:cout
    std::cout << id << e.what() << "\n";
  }
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(print_thread_id,i+1);

  for (auto& th : threads) th.join();

  return 0;
}