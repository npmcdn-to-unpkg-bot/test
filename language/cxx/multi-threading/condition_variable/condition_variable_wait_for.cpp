// condition_variable::wait_for example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>             // std::chrono::seconds
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable, std::cv_status


/*
public member function
<condition_variable>
std::condition_variable::wait_for


unconditional (1)   
template <class Rep, class Period>
  cv_status wait_for (unique_lock<mutex>& lck,
                      const chrono::duration<Rep,Period>& rel_time);


predicate (2)   
template <class Rep, class Period, class Predicate>
       bool wait_for (unique_lock<mutex>& lck,
                      const chrono::duration<Rep,Period>& rel_time, Predicate pred);


Wait for timeout or until notified
The execution of the current thread (which shall have locked lck's mutex) is blocked during rel_time, or until notified (if the latter happens first).

At the moment of blocking the thread, the function automatically calls lck.unlock(), allowing other locked threads to continue.

Once notified or once rel_time has passed, the function unblocks and calls lck.lock(), leaving lck in the same state as when the function was called. Then the function returns (notice that this last mutex locking may block again the thread before returning).

Generally, the function is notified to wake up by a call in another thread either to member notify_one or to member notify_all. But certain implementations may produce spurious wake-up calls without any of these functions being called. Therefore, users of this function shall ensure their condition for resumption is met.

If pred is specified (2), the function only blocks if pred returns false, and notifications can only unblock the thread when it becomes true (which is especially useful to check against spurious wake-up calls). It behaves as if implemented as:
 
return wait_until (lck, chrono::steady_clock::now() + rel_time, std::move(pred));


Parameters
lck
  A unique_lock object whose mutex object is currently locked by this thread.
  All concurrent calls to wait member functions of this object shall use the same underlying mutex object (as returned by lck.mutex()).
rel_time
  The maximum time span during which the thread will block waiting to be notified.
  duration is an object that represents a specific relative time.
pred
  A callable object or function that takes no arguments and returns a value that can be evaluated as a bool.
  This is called repeatedly until it evaluates to true.

Return value
  The unconditional version (1) returns cv_status::timeout if the function returns because rel_time has passed, or cv_status::no_timeout otherwise.
  The predicate version (2) returns pred(), regardless of whether the timeout was triggered (although it can only be false if triggered).

*/


std::condition_variable cv;

int value;

void read_value() {
  std::cin >> value;
  cv.notify_one();
}

int main ()
{
  std::cout << "Please, enter an integer (I'll be printing dots): ";
  std::thread th (read_value);

  std::mutex mtx;
  std::unique_lock<std::mutex> lck(mtx);
  while (cv.wait_for(lck,std::chrono::seconds(1))==std::cv_status::timeout) {
    std::cout << '.';
  }
  std::cout << "You entered: " << value << '\n';

  th.join();

  return 0;
}
