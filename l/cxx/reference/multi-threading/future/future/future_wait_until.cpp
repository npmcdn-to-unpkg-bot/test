
template <class Clock, class Duration>
  future_status wait_until (const chrono::time_point<Clock,Duration>& abs_time) const;
Wait for ready until time point
Waits for the shared state to be ready, at most until abs_time.

If the shared state is not yet ready (i.e., the provider has not yet set its value or exception), the function blocks the calling thread and waits until it is ready or until abs_time, whichever comes first.

When the function returns because its shared state is made ready, the value or exception set on the shared state is nor read, but all visible side effects are synchronized between the point the provider makes the shared state ready and the return of this function.

If the shared state contains a deferred function (such as future objects returned by async), the function does not block, returning immediately with a value of future_status::deferred.
