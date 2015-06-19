#include <future>
#include <iostream>

/*

template <class T>  shared_future;
template <class R&> shared_future<R&>;   // specialization : T is a reference type (R&)
template <>         shared_future<void>; // specialization : T is void


Shared future
A shared_future object behaves like a future object, except that it can be copied, 
                                                                            ^^^^
and that more than one shared_future can share ownership over their end of a shared state. 
They also allow the value in the shared state to be retrieved multiple times once ready.
                                                              ^^^^^^^^^^^^^^

shared_future objects can be implicitly converted from future objects (see its constructor),
 or explicitly obtained by calling future::share. In both cases, the future object from which 
 it is obtained transfers its association with the shared state to the shared_future and 
 becomes itself non-valid.

The lifetime of the shared state lasts at least until the last object with which it is 
associated is destroyed. Retrieving the value from a shared_future (with member get) 
does not release its ownership over the shared state (unlike with futures). Therefore, 
if associated to shared_future objects, the shared state can survive the object from 
which it was obtained in the first place (if any).

Member functions
-------------------------------------------
(constructor)       Construct shared_future (public member function )
(destructor)        Destroy shared_future (public member function )
operator=           Assign shared future (public member function )
get                 Get value (public member function )
valid               Check for valid shared state (public member function )
wait                Wait for ready (public member function )
wait_for            Wait for ready during time span (public member function )
wait_until          Wait for ready until time point (public member function )

*/

int echo_value(int i) {
    return i;
}

int main() {
    std::future<int> bar = std::async(echo_value, 11);
    std::shared_future<int> foo(std::move(bar));

    std::cout << "First  get: " << foo.get() << std::endl;
    std::cout << "Second get: " << foo.get() << std::endl;
    std::cout << "Third  get: " << foo.get() << std::endl;

    std::future<int> coo = std::async(echo_value, 22);
    std::cout << "First  get: " << coo.get() << std::endl;
    std::cout << "Second get: " << coo.get() << std::endl; // exception here.
    std::cout << "Third  get: " << coo.get() << std::endl;
}