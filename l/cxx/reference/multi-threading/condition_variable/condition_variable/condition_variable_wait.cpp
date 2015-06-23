// condition_variable::wait (with predicate)
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable


/*
public member function
<condition_variable>
std::condition_variable::wait

unconditional (1) 
void wait (unique_lock<mutex>& lck);


predicate (2) 
template <class Predicate>
  void wait (unique_lock<mutex>& lck, Predicate pred);


  
Wait until notified
The execution of the current thread (which shall have locked lck's mutex) is blocked until notified.

At the moment of blocking the thread, the function automatically calls lck.unlock(), allowing other locked threads to continue.

Once notified (explicitly, by some other thread), the function unblocks and calls lck.lock(), leaving lck in the same state as when the function was called. Then the function returns (notice that this last mutex locking may block again the thread before returning).

Generally, the function is notified to wake up by a call in another thread either to member notify_one or to member notify_all. But certain implementations may produce spurious wake-up calls without any of these functions being called. Therefore, users of this function shall ensure their condition for resumption is met.

If pred is specified (2), the function only blocks if pred returns false, and notifications can only unblock the thread when it becomes true (which is specially useful to check against spurious wake-up calls). This version (2) behaves as if implemented as:
 
while (!pred()) wait(lck);
*/



std::mutex mtx;
std::condition_variable cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}

void consume (int n) {
  for (int i=0; i<n; ++i) {
    std::unique_lock<std::mutex> lck(mtx);
    cv.wait(lck,shipment_available);
    // consume:
    std::cout << cargo << '\n';
    cargo=0;
  }
}

int main ()
{
  std::thread consumer_thread (consume,10);

  // produce 10 items when needed:
  for (int i=0; i<10; ++i) {
    while (shipment_available()) {
      std::cout << "ready to ship" << std::endl;
      std::this_thread::yield();
    }
    std::unique_lock<std::mutex> lck(mtx);
    cargo = i+1;
    cv.notify_one();
  }

  consumer_thread.join();

  return 0;
}