// atomic_flag as a spinning lock
#include <iostream>       // std::cout
#include <atomic>         // std::atomic_flag
#include <thread>         // std::thread
#include <vector>         // std::vector
#include <sstream>        // std::stringstream

/*

std::atomic_flag

struct atomic_flag;
Atomic flag
Atomic flags are boolean atomic objects that support two operations: test-and-set and clear.

Atomic flags are lock-free (this is the only type guaranteed to be lock-free on all library implementations).

*/


/*

public member function
<atomic>
std::atomic_flag::test_and_set
bool test_and_set (memory_order sync = memory_order_seq_cst) volatile noexcept;
bool test_and_set (memory_order sync = memory_order_seq_cst) noexcept;
Test and set flag
Sets the atomic_flag and returns whether it was already set immediately before the call.

The entire operation is atomic (an atomic read-modify-write operation):
    ^^^^^^              ^^^^^^
the value is not affected by other threads between the instant its value is read (to be returned) and the moment it is modified by this function.

Parameters
sync
    Synchronization mode for the operation.
    This can be any of the possible values of the enum type memory_order:
    value                   memory order    description
    --------------------------------------------------------------------------------
    memory_order_relaxed    Relaxed                 No synchronization of side effects.
    memory_order_consume    Consume                 Synchronizes the visible side effects on values carrying dependencies from the last release or sequentially consistent operation.
    memory_order_acquire    Acquire                 Synchronizes all visible side effects from the last release or sequentially consistent operation.
    memory_order_release    Release                 Synchronizes side effects with the next consume or acquire operation.
    memory_order_acq_rel    Acquire/Release         Reads as an acquire operation and writes as a release operation (as described above).
    memory_order_seq_cst    Sequentially consistent Synchronizes all visible side effects with the other sequentially consistent operations, following a single total order.

Return value
    true if the flag was set before the call.
    false otherwise.

*/

std::atomic_flag lock_stream = ATOMIC_FLAG_INIT;
std::stringstream stream;

void append_number(int x) {
  while (lock_stream.test_and_set()) {
    std::cout << x;
  }
  std::cout << std::endl;
  
  stream << "thread #" << x << '\n';
  lock_stream.clear();
}

int main ()
{
  std::vector<std::thread> threads;
  for (int i=1; i<=10; ++i) threads.push_back(std::thread(append_number,i));
  for (auto& th : threads) th.join();

  std::cout << stream.str();
  return 0;
}