#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

struct Box {
  explicit Box(int num) : num_things{num} {}
 
  int num_things;
  std::mutex m;
};
 
void transfer(Box &from, Box &to, int num) {
  using namespace std::literals::chrono_literals;


  // don't actually lock the mutexs yet
  std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
  std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
 
  // lock both unique_locks without deadlock
  std::lock(lock1, lock2);


  from.num_things -= num;
  to.num_things += num;

  from.m.unlock();
  to.m.unlock();
}
 
int main() {
  Box acc1(100);
  Box acc2(50);
 
  // "The capture, sensibly, defaults to capture by value because otherwise things would fail horribly if the parameter went away before the thread could read it. You need to explicitly ask for this behavior so that there's something to indicate that you are assuming responsibility for ensuring that the target of the reference is still valid."
  std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
  std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
 
  t1.join();
  t2.join();
  
  std::cout << acc1.num_things << std::endl;
}
