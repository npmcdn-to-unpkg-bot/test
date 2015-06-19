// packaged_task example
#include <iostream>     // std::cout
#include <future>       // std::packaged_task, std::future
#include <chrono>       // std::chrono::seconds
#include <thread>       // std::thread, std::this_thread::sleep_for



/*
template <class T> packaged_task;     // undefined
template <class Ret, class... Args> class packaged_task<Ret(Args...)>;
Packaged task
A packaged_task wraps a callable element and allows its result to be retrieved asynchronously.

It is similar to std::function, but transferring its result automatically to a future object.

The object contains internally two elements:
A stored task, which is some callable object (such as a function pointer, pointer to member 
or function object) whose call signature shall take arguments of the types in Args...
 and return a value of type Ret.
A shared state, which is able to store the results of calling the stored task (of type Ret) 
and be accessed asynchronously through a future.

The shared state is associated to a future object by calling member get_future. 
After the call, both objects share the same shared state:
  - The packaged_task object is the asynchronous provider and is expected to set the 
    shared state as ready at some point by calling the stored task.
  - The future object is an asynchronous return object that can retrieve the value of 
  the shared state, waiting for it to be ready, if necessary.

The lifetime of the shared state lasts at least until the last object with which it is
 associated releases it or is destroyed. Therefore it can survive the packaged_task object 
 that obtained it in the first place if associated also to a future.
*/


// count down taking a second for each value:
int countdown (int from, int to) {
  for (int i=from; i!=to; --i) {
    std::cout << i << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Lift off!\n";
  return from - to;
}

int main ()
{
  std::packaged_task<int(int,int)> tsk (countdown);   // set up packaged_task
  std::future<int> ret = tsk.get_future();            // get future

  std::thread th (std::move(tsk),10,0);   // spawn thread to count down from 10 to 0

  // ...

  int value = ret.get();                  // wait for the task to finish and get result

  std::cout << "The countdown lasted for " << value << " seconds.\n";

  th.join();

  return 0;
}