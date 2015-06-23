// condition_variable_any::wait (with predicate)
#include <iostream>           // std::cout
#include <thread>             // std::thread, std::this_thread::yield
#include <mutex>              // std::mutex
#include <condition_variable> // std::condition_variable_any

/*
class
<condition_variable>
std::condition_variable_any


class condition_variable_any;


Condition variable (any lock)
Same as condition_variable, except that its wait functions can take any lockable type as argument 
(condition_variable objects can only take unique_lock<mutex>).
Other than that, they are identical.
                         ^^^^^^^^^

Member functions
(constructor)
  Construct condition_variable_any (public member function )
(destructor)
  Destroy condition_variable_any (public member function )

Wait functions
wait
  Wait until notified (public member function )
wait_for
  Wait for timeout or until notified (public member function )
wait_until
  Wait until notified or time point (public member function )

Notify functions
notify_one
  Notify one (public member function )
notify_all
  Notify all (public member function )
*/



std::mutex mtx;
std::condition_variable_any cv;

int cargo = 0;
bool shipment_available() {return cargo!=0;}

void consume (int n) {
  for (int i=0; i<n; ++i) {
    mtx.lock(); // need to do this by ourself
    cv.wait(mtx,shipment_available);
    // consume:
    std::cout << cargo << '\n';
    cargo=0;
    mtx.unlock(); // need to do this by ourself
  }
}

int main ()
{
  std::thread consumer_thread (consume,10);

  // produce 10 items when needed:
  for (int i=0; i<10; ++i) {
    while (shipment_available()) std::this_thread::yield();
    mtx.lock(); // need to do this by ourself
    cargo = i+1;
    cv.notify_one();
    mtx.unlock(); // need to do this by ourself
  }

  consumer_thread.join();

  return 0;
}