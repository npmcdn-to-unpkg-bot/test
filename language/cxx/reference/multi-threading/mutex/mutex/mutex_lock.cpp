// mutex::lock/unlock
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex



/*
td::mutex::lock
void lock();
Lock mutex
The calling thread locks the mutex, blocking if necessary:

If the mutex isn't currently locked by any thread, the calling thread locks it (from this point, and until its member unlock is called, the thread owns the mutex).
If the mutex is currently locked by another thread, execution of the calling thread is blocked until unlocked by the other thread (other non-locked threads continue their execution).
If the mutex is currently locked by the same thread calling this function, it produces a deadlock (with undefined behavior). See recursive_mutex for a mutex type that allows multiple locks from the same thread.

All lock and unlock operations on the mutex follow a single total order, with all visible effects synchronized between the lock operations and previous unlock operations on the same object.

The non-member function lock allows to lock more than one mutex object simultaneously, avoiding the potential deadlocks that can happen when multiple threads lock/unlock individual mutex objects in different orders.

Note that the order in which different concurrent locks are scheduled to return is unspecified, and not necessarily related to the order in which they are locked (depending on the system and library implementation).

Parameters
none

Return value
none
*/


std::mutex mtx;           // mutex for critical section

void print_thread_id (int id) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  std::cout << "thread #" << id << '\n';
  mtx.unlock();
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
Edit & Run
