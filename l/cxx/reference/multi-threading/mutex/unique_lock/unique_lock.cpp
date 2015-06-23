// unique_lock example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock

/*

template <class Mutex> class unique_lock;
Unique lock
A unique lock is an object that manages a mutex object with unique ownership in both states: locked and unlocked.

On construction (or by move-assigning to it), the object acquires a mutex object, 
for whose locking and unlocking operations becomes responsible.

The object supports both states: locked and unlocked.

This class guarantees an unlocked status on destruction (even if not called explicitly). 
Therefore it is especially useful as an object with automatic duration, 
as it guarantees the mutex object is properly unlocked in case an exception is thrown.

Note though, that the unique_lock object does not manage the lifetime of the mutex object in any way: 
the duration of the mutex object shall extend at least until the destruction of the unique_lock that manages it.

*/


std::mutex mtx;           // mutex for critical section

void print_block (int n, char c) {
  // critical section (exclusive access to std::cout signaled by lifetime of lck):
  std::unique_lock<std::mutex> lck (mtx);
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
}

int main ()
{
  std::thread th1 (print_block,50,'*');
  std::thread th2 (print_block,50,'$');

  th1.join();
  th2.join();

  return 0;
}