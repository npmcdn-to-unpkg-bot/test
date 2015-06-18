// std::lock example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::try_lock

/*
template <class Mutex1, class Mutex2, class... Mutexes>
  int try_lock (Mutex1& a, Mutex2& b, Mutexes&... cde);
Try to lock multiple mutexes
Attempts to lock all the objects passed as arguments using their try_lock member functions (non-blocking).

The function calls the try_lock member function for each argument 
(first a, then b, and eventually the others in cde, in the same order), 
until either all calls are successful, or as soon as one of the calls fails 
(either by returning false or throwing an exception).

If the function ends because a call fails, unlock is called on all objects for which the call 
to try_lock was successful, and the function returns the argument order number of the object 
whose lock failed. No further calls are performed for the remaining objects in the argument list.
*/


std::mutex foo,bar;

void task_a () {
  foo.lock();
  std::cout << "task a\n";
  bar.lock();
  // ...
  foo.unlock();
  bar.unlock();
}

void task_b () {
  int x = try_lock(bar,foo);
  if (x==-1) {
    std::cout << "task b\n";
    // ...
    bar.unlock();
    foo.unlock();
  }
  else {
    std::cout << "[task b failed: mutex " << (x?"foo":"bar") << " locked]\n";
  }
}

int main ()
{
  std::thread th1 (task_a);
  std::thread th2 (task_b);

  th1.join();
  th2.join();

  return 0;
}