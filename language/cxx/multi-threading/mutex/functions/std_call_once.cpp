// call_once example
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::milliseconds
#include <mutex>          // std::call_once, std::once_flag


/*

template <class Fn, class... Args>
  void call_once (once_flag& flag, Fn&& fn, Args&&... args);
Call function once
Calls fn passing args as arguments, unless another thread has already 
executed (or is currently executing) a call to call_once with the same flag.

If another thread is already actively executing a call to call_once with the same flag, 
it causes a passive execution: Passive executions do not call fn but do not return until 
the active execution itself has returned, and all visible side effects are synchronized 
at that point among all concurrent calls to this function with the same flag.

If an active call to call_once ends by throwing an exception (which is propagated to its
 calling thread) and passive executions exist, one is selected among these passive executions, 
 and called to be the new active call instead.

Note that once an active execution has returned, all current passive executions and future 
calls to call_once (with the same flag) also return without becoming active executions.

The active execution uses decay copies of the lvalue or rvalue references of fn and args, 
ignoring the value returned by fn.

*/

/*
std::once_flag
struct once_flag;
Flag argument type for call_once
Object of this type are used as arguments for call_once.

Using the same object on different calls to call_once in different threads causes a single execution if called concurrently.

It is a non-copyable, non-movable, default-constructible class, declared in <mutex> with the following prototype:

struct once_flag {
  constexpr once_flag() noexcept;
  once_flag (const once_flag&) = delete;
  once_flag& operator= (const once_flag&) = delete;
};


*/


int winner;
void set_winner (int x) { winner = x; }
std::once_flag winner_flag;

void wait_1000ms (int id) {
  // count to 1000, waiting 1ms between increments:
  for (int i=0; i<1000; ++i)
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  // claim to be the winner (only the first such call is executed):
  std::call_once (winner_flag,set_winner,id);
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(wait_1000ms,i+1);

  std::cout << "waiting for the first among 10 threads to count 1000 ms...\n";

  for (auto& th : threads) th.join();
  std::cout << "winner thread: " << winner << '\n';

  return 0;
}