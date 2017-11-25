#include <chrono>
#include <iostream>
#include <thread>

int main() {  
  using namespace std::chrono_literals;

  int numIterations = 10;
  
  // TODO: add sleeps to see what race conditions exist
  // TODO: what happens if we capture by value
  auto lamdaFunc = [&numIterations]() {
    // std::this_thread::sleep_for(1s);
    for (int i = 0; i < numIterations; ++i) {
      std::cout << "Thread id: " << std::this_thread::get_id();
      std::cout << " value = " << i << std::endl;
    }
  };

  std::thread t1{lamdaFunc};
  // std::this_thread::sleep_for(1s);
  numIterations = 5;
  std::thread t2{lamdaFunc};
  t1.join();  
  t2.join();
}
