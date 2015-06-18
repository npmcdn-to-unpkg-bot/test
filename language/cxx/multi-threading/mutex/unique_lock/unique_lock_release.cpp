// unique_lock::release example
#include <iostream>       // std::cout
#include <vector>         // std::vector
#include <thread>         // std::thread
#include <mutex>          // std::mutex, std::unique_lock


/*

mutex_type* release() noexcept;
Release mutex
Returns a pointer to the managed mutex object, releasing ownership over it.

After the call, the unique_lock object no longer manages any mutex object (i.e., it is left in the same state as a if default-constructed).

Note that this function does not lock nor unlock the returned mutex object.

Parameters
none

Return value
A pointer to the mutex object managed by the unique_lock before the call.

*/



std::mutex mtx;
int count = 0;

void print_count_and_unlock (std::mutex* p_mtx) {
  std::cout << "count: " << count << '\n';
  p_mtx->unlock();
}

void task() {
  std::unique_lock<std::mutex> lck(mtx);
  ++count;
  print_count_and_unlock(lck.release());
}

int main ()
{
  std::vector<std::thread> threads;
  for (int i=0; i<10; ++i)
    threads.emplace_back(task);

  for (auto& x: threads) x.join();

  return 0;
}
