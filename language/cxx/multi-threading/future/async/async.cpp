// async example
#include <iostream>       // std::cout
#include <future>         // std::async, std::future


/*


unspecified policy (1)  
    template <class Fn, class... Args>
      future<typename result_of<Fn(Args...)>::type>
        async (Fn&& fn, Args&&... args);
specific policy (2) 
    template <class Fn, class... Args>
      future<typename result_of<Fn(Args...)>::type>
        async (launch policy, Fn&& fn, Args&&... args);
Call function asynchronously
Calls fn (with args as arguments) at some point, returning without waiting for the execution of fn to complete.

The value returned by fn can be accessed through the future object returned (by calling its member future::get).

The second version (2) lets the caller select a specific launching policy, while the first version (1) uses automatic selection, as if calling (2) with launch::async|launch::deferred as policy.

The function temporarily stores in the shared state either the threading handler used or decay copies of fn and args (as a deferred function) without making it ready. Once the execution of fn is completed, the shared state contains the value returned by fn and is made ready.

Parameters
policy
A bitmask value of type launch indicating the launching policy:
policy  description
launch::async   Asynchronous: Launches a new thread to call fn (as if a thread object is constructed with fn and args as arguments, and accessing the shared state of the returned future joins it).
launch::deferred    Deferred: The call to fn is deferred until the shared state of the returned future is accessed (with wait or get). At that point, fn is called and the function is no longer considered deferred. When this call returns, the shared state of the returned future is made ready.
launch::async|launch::deferred  Automatic: The function chooses the policy automatically (at some point). This depends on the system and library implementation, which generally optimizes for the current availability of concurrency in the system.
Particular library implementations may support additional launching policies, with the proper label defined in type launch. Combining multiple values is possible, in which case, the function automatically chooses one among them.
fn
A pointer to function, pointer to member, or any kind of move-constructible function object (i.e., an object whose class defines operator(), including closures and function objects).
The function uses a decay copy of this argument.
The return value of fn is stored as the shared state to be retrieved by the future object returned by async.
If fn throws, the exception is set in the shared state to be retrieved by the future object.
args...
Arguments passed to the call to fn (if any). Their types shall be move-constructible.
If fn is a member pointer, the first argument shall be an object for which that member is defined (or a reference, or a pointer to it).
The function uses decay copies of these arguments.
Fn and Args... are template parameters: if implicitly deduced, these are the proper lvalue or rvalue reference types of the arguments. Note though, that the function uses decay copies of fn and args... (see std::ref for a wrapper class that makes references copyable).

Return value
A future object whose shared state is made ready when the execution of fn ends. The value retrieved by its member future::get is the value returned by fn (if any).

When launch::async is selected, the future returned is linked to the end of the thread created, even if its shared state is never accessed: in this case, its destructor synchronizes with the return of fn. Therefore, the return value shall not be disregarded for asynchronous behavior, even when fn returns void.

result_of::type is the type returned by Fn when called with arguments of the types in Args.

*/


// a non-optimized way of checking for prime numbers:
bool is_prime (int x) {
  std::cout << "This is is_prime thread " << pthread_self() << std::endl;
  std::cout << "Calculating. Please, wait...\n";
  for (int i=2; i<x; ++i) if (x%i==0) return false;
  return true;
}

int main ()
{
  std::cout << "This is main thread     " << pthread_self() << std::endl;

  // call is_prime(313222313) asynchronously:
  std::future<bool> fut = std::async (is_prime,313222313);

  std::cout << "Checking whether 313222313 is prime.\n";
  // ...

  bool ret = fut.get();      // waits for is_prime to return

  if (ret) std::cout << "It is prime!\n";
  else std::cout << "It is not prime.\n";

  return 0;
}