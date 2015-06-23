// future example
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
#include <chrono>         // std::chrono::milliseconds
#include <thread>


/*

Future
A future is an object that can retrieve a value from some provider object or function,
properly synchronizing this access if in different threads.

"Valid" futures are future objects associated to a shared state, and are constructed
by calling one of the following functions:

  - async
  - promise::get_future
  - packaged_task::get_future

future objects are only useful when they are valid. Default-constructed future objects are not
valid (unless move-assigned a valid future).

Calling future::get on a valid future blocks the thread until the provider makes the shared state
ready (either by setting a value or an exception to it). This way, two threads can be synchronized
by one waiting for the other to set a value.

The lifetime of the shared state lasts at least until the last object with which it is associated
releases it or is destroyed. Therefore, if associated to a future, the shared state can survive
the object from which it was obtained in the first place (if any).

*/


// a non-optimized way of checking for prime numbers:
bool is_prime (int x) {
  std::cout << "is_prime runs in " << pthread_self() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}

int main ()
{
  std::cout << "main runs in " << pthread_self() << std::endl;
  // call function asynchronously:
  std::future<bool> fut = std::async (is_prime,444444443); 

  // do something while waiting for function to set future:
  std::cout << "checking, please wait";
  std::chrono::milliseconds span (100);
  while (fut.wait_for(span)==std::future_status::timeout)
    std::cout << '.' << std::flush;

  bool x = fut.get();     // retrieve return value

  std::cout << "\n444444443 " << (x?"is":"is not") << " prime.\n";

  return 0;
}