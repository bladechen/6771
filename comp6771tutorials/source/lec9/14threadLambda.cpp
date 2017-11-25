#include <iostream>
#include <thread>

int main() {
  auto lamdaFunc = [](int numIterations) {
    for (int i = 0; i < numIterations; ++i) {
      std::cout << "Thread id: " << std::this_thread::get_id();
      std::cout << " value = " << i << std::endl;
    }
  };
  
  std::thread t1{lamdaFunc,10};
  std::thread t2{lamdaFunc,5};
  t1.join();  
  t2.join();
}
