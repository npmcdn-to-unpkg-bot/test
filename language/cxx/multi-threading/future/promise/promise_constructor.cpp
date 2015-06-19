// promise constructors
#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <memory>         // std::allocator, std::allocator_arg
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

void print_int (std::future<int>& fut1, std::future<int>& fut2) {
  std::cout << "Start to wait future 2 of coo" << std::endl;
  int x2 = fut2.get(); // block until coo set_value.
  std::cout << "Start to wait future 1 of bar" << std::endl;
  int x1 = fut1.get();
  // int x2 = fut2.get();
  std::cout << "value 1: " << x1 << ", value2 :" << x2 << '\n';

}

int main ()
{
  std::promise<int> foo;
  std::promise<int> bar = std::promise<int>(std::allocator_arg,std::allocator<int>());
  std::promise<int> coo(std::move(foo));

  std::future<int> fut1 = bar.get_future();
  std::future<int> fut2 = coo.get_future();

  std::thread th (print_int, std::ref(fut1), std::ref(fut2));
  std::this_thread::sleep_for(std::chrono::seconds(1));

  std::cout << "set bar 20" << std::endl;
  bar.set_value (20);
  std::cout << "sleep 3 seconds" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::cout << "set coo 30" << std::endl;
  coo.set_value (30);



  th.join();
  return 0;
}