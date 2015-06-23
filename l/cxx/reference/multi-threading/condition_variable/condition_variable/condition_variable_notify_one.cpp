// condition_variable::notify_one
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable


/* 
public member function

<condition_variable>
std::condition_variable::notify_one

void notify_one() noexcept;

Notify one
Unblocks one of the threads currently waiting for this condition.

If no threads are waiting, the function does nothing.

If more than one, it is unspecified which of the threads is selected.

Parameters
none

Return value
none
*/


std::mutex mtx;
std::condition_variable produce,consume;

int cargo = 0;     // shared value by producers and consumers

void consumer (int thread_id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (cargo==0) {
    std::cout << "consumer " << thread_id << " start to wait" << std::endl;
    consume.wait(lck);
    std::cout << "consumer " << thread_id << " stop waitting" << std::endl;
  }
  std::cout << "consumer " << thread_id << ", cargo:" << cargo << '\n';
  cargo=0;
  produce.notify_one();
}

void producer (int id, int thread_id) {
  std::unique_lock<std::mutex> lck(mtx);
  while (cargo!=0)  {
    std::cout << "producer " << thread_id << " waiting for cargo is consumed" << std::endl;
    produce.wait(lck);
    std::cout << "producer " << thread_id << " start to load cargo" << std::endl;
  }
  cargo = id;
  std::cout << "producer " << thread_id << " start to notify_one" << std::endl;
  consume.notify_one();
}

int main ()
{
  std::thread consumers[10],producers[10];
  // spawn 10 consumers and 10 producers:
  for (int i=0; i<10; ++i) {
    consumers[i] = std::thread(consumer, i);
    producers[i] = std::thread(producer,i+1, i);
  }

  // join them back:
  for (int i=0; i<10; ++i) {
    producers[i].join();
    consumers[i].join();
  }

  return 0;
}