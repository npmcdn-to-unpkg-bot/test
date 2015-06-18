// mutex::try_lock example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex


/*

std::mutex::try_lock
bool try_lock();
Lock mutex if not locked
Attempts to lock the mutex, without blocking:
If the mutex isn't currently locked by any thread, the calling thread locks it (from this point, and until its member unlock is called, the thread owns the mutex).
If the mutex is currently locked by another thread, the function fails and returns false, without blocking (the calling thread continues its execution).
If the mutex is currently locked by the same thread calling this function, it produces a deadlock (with undefined behavior). See recursive_mutex for a mutex type that allows multiple locks from the same thread.

This function may fail spuriously when no other thread has a lock on the mutex, but repeated calls in these circumstances shall succeed at some point.

All lock and unlock operations on the mutex follow a single total order, with all visible effects synchronized between the lock operations and previous unlock operations on the same object.

Parameters
none

Return value
true if the function succeeds in locking the mutex for the thread.
false otherwise.
*/



volatile int counter (0); // non-atomic counter
std::mutex mtx;           // locks access to counter

void attempt_10k_increases () {
  for (int i=0; i<10000; ++i) {
    if (mtx.try_lock()) {   // only increase if currently not locked:
      ++counter;
      mtx.unlock();
    }
  }
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(attempt_10k_increases);

  for (auto& th : threads) th.join();
  std::cout << counter << " successful increases of the counter.\n";

  return 0;
}
Edit & Run
