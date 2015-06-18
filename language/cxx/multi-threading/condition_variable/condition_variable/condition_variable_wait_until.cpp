/*


<condition_variable>
std::condition_variable::wait_until


unconditional (1)   
template <class Clock, class Duration>
  cv_status wait_until (unique_lock<mutex>& lck,
                        const chrono::time_point<Clock,Duration>& abs_time);
predicate (2)   
template <class Clock, class Duration, class Predicate>
       bool wait_until (unique_lock<mutex>& lck,
                        const chrono::time_point<Clock,Duration>& abs_time,
                        Predicate pred);


Wait until notified or time point
The execution of the current thread (which shall have locked lck's mutex) is blocked either until notified or until abs_time, whichever happens first.

At the moment of blocking the thread, the function automatically calls lck.unlock(), allowing other locked threads to continue.

Once notified or once it is abs_time, the function unblocks and calls lck.lock(), leaving lck in the same state as when the function was called. Then the function returns (notice that this last mutex locking may block again the thread before returning).

Generally, the function is notified to wake up by a call in another thread either to member notify_one or to member notify_all. But certain implementations may produce spurious wake-up calls without any of these functions being called. Therefore, users of this function shall ensure their condition for resumption is met.

If pred is specified (2), the function only blocks if pred returns false, and notifications can only unblock the thread when it becomes true (which is especially useful to check against spurious wake-up calls). It behaves as if implemented as:

    while (!pred())
      if ( wait_until(lck,abs_time) == cv_status::timeout)
        return pred();
    return true;


Parameters
lck
    A unique_lock object whose mutex object is currently locked by this thread.
    All concurrent calls to wait member functions of this object shall use the same underlying mutex object (as returned by lck.mutex()).
abs_time
    A point in time at which the thread will stop blocking, allowing the function to return.
    time_point is an object that represents a specific absolute time.
pred
    A callable object or function that takes no arguments and returns a value that can be evaluated as a bool.
    This is called repeatedly until it evaluates to true.

Return value
    The unconditional version (1) returns cv_status::timeout if the function returns because abs_time has been reached, or cv_status::no_timeout otherwise.
    The predicate version (2) returns pred(), regardless of whether the timeout was triggered (although it can only be false if triggered).

Data races
The function performs three atomic operations:
The initial unlocking of lck and simultaneous entry into the waiting state.
The unblocking of the waiting state.
The locking of lck before returning.
Atomic operations on the object are ordered according to a single total order, with the three atomic operations in this function happening in the same relative as above.

*/
