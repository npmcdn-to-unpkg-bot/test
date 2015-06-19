// unique_lock constructor example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::lock, std::unique_lock
                          // std::adopt_lock, std::defer_lock

/*

std::unique_lock::unique_lock
default (1)           unique_lock() noexcept;
locking (2)           explicit unique_lock (mutex_type& m);
try-locking (3)       unique_lock (mutex_type& m, try_to_lock_t tag);
deferred (4)          unique_lock (mutex_type& m, defer_lock_t tag) noexcept;
adopting (5)          unique_lock (mutex_type& m, adopt_lock_t tag);
locking for (6) 
                      template <class Rep, class Period>
                      unique_lock (mutex_type& m, const chrono::duration<Rep,Period>& rel_time);
locking until (7) 
                      template <class Clock, class Duration>
                      unique_lock (mutex_type& m, const chrono::time_point<Clock,Duration>& abs_time);
copy [deleted] (8)    unique_lock (const unique_lock&) = delete;
move (9)  unique_lock (unique_lock&& x);


(1) default constructor
  The object manages no mutex object.
(2) locking initialization
  The object manages m, and locks it (blocking, if necessary) by calling m.lock().
(3) try-locking initialization
  The object manages m, and attempts to lock it (without blocking) by calling m.try_lock().
(4) deferred initialization
  The object manages m without locking it. m shall be a mutex object that is not currently locked by the constructing thread.
(5) adopting initialization
  The object manages m, which is a mutex object currently locked by the constructing thread (the object acquires ownership over the lock).
(6) locking for duration
  The object manages m, and attempts to lock it during rel_time by calling m.try_lock_for(rel_time).
(7) locking until time point
  The object manages m, and attempts to lock it before abs_time by calling m.try_lock_until(abs_time).
(8) copy construction [deleted]
  unique_lock objects cannot be copied (copy constructor deleted).
(9) move construction
  The object acquires the mutex managed by x, including its current owning state.
  x is left in the same state as if default-constructed (referring to no mutex object).

The object manages the state of a mutex object by keeping a reference to it and information on whether it owns a lock on it.

Objects constructed with (2) and (5) always own a lock on the mutex object. Those with (1) and (4) never own a lock. For (3), (6) and (7), they own a lock if the locking attempt is successful.

Parameters
m
    mutex object to be managed by the unique_lock object.
    mutex_type is unique_lock's template parameter (the type of the managed mutex object).
tag
    This tag argument is merely used to select a specific constructor (values of these types have no state).
    It is one of the following values:

    value description
    ------------------------------------------------------------
    (no tag)      Lock on construction by calling member lock.
    try_to_lock   Attempt to lock on construction by calling member try_lock
    defer_lock    Do not lock on construction (and assume it is not already locked by thread)
    adopt_lock    Adopt current lock (assume it is already locked by thread).
    ------------------------------------------------------------

    try_to_lock_t, defer_lock_t and adopt_lock_t are the types of objects try_to_lock, defer_lock and adopt_lock, respectively.

  
rel_time
    The maximum time span during which the thread could block waiting to acquire a lock. If exhausted, the object is initialized not owning a lock.
    duration is an object that represents a specific relative time.
abs_time
    A point in time at which the thread will stop blocking waiting to acquire a lock. If reached, the object is initialized not owning a lock.
    time_point is an object that represents a specific absolute time.
x
    Another unique_lock object.


*/

std::mutex foo,bar;

void task_a () {
  std::lock (foo,bar);         // simultaneous lock (prevents deadlock)
  std::unique_lock<std::mutex> lck1 (foo,std::adopt_lock);
  std::unique_lock<std::mutex> lck2 (bar,std::adopt_lock);
  std::cout << "task a\n";
  // (unlocked automatically on destruction of lck1 and lck2)
}

void task_b () {
  // foo.lock(); bar.lock(); // replaced by:
  std::unique_lock<std::mutex> lck1, lck2;
  lck1 = std::unique_lock<std::mutex>(bar,std::defer_lock);
  lck2 = std::unique_lock<std::mutex>(foo,std::defer_lock);
  std::lock (lck1,lck2);       // simultaneous lock (prevents deadlock)
  std::cout << "task b\n";
  // (unlocked automatically on destruction of lck1 and lck2)
}


int main ()
{
  std::thread th1 (task_a);
  std::thread th2 (task_b);

  th1.join();
  th2.join();

  return 0;
}