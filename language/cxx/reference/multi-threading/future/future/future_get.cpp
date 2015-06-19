// future::get
#include <iostream>       // std::cout, std::ios
#include <future>         // std::async, std::future
#include <exception>      // std::exception


/*

std::future::get

generic template (1)          T get();
reference specialization (2)  R& future<R&>::get();       // when T is a reference type (R&)
void specialization (3)       void future<void>::get();   // when T is void

Get value
Returns the value stored in the shared state (or throws its exception) when the shared state is ready.

If the shared state is not yet ready (i.e., the provider has not yet set its value or exception),
the function blocks the calling thread and waits until it is ready.

Once the shared state is ready, the function unblocks and returns (or throws) releasing its
shared state. This makes the future object no longer valid: this member function shall be called
once at most for every future shared state.

All visible side effects are synchronized between the point the provider makes the shared state
ready and the return of this function.

The member of the void specialization (3) does not return any value, but still waits for the
shared state to become ready and releases it.

*/


int get_int() {
  std::cin.exceptions (std::ios::failbit);   // throw on failbit set
  int x;
  std::cin >> x;                             // sets failbit if invalid
  return x;
}

int main ()
{
  std::future<int> fut = std::async (get_int);

  std::cout << "Please, enter an integer value: ";

  try {
    int x = fut.get();
    std::cout << "You entered: " << x << '\n';
  }
  catch (std::exception&) {
    std::cout << "[exception caught]";
  }

  return 0;
}