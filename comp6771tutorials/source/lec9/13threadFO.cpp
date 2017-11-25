#include <iostream>
#include <thread>

struct Counter {
  int numIterations;
  Counter(int n) : numIterations{n} {}  // constructor
  void operator()() {
    for (int i = 0; i < numIterations; ++i) {
      std::cout << "Thread id: " << std::this_thread::get_id();
      std::cout << " value = " << i << std::endl;
    }
  }
};

int main() {
  // uniform initisation
  std::thread t1 { Counter { 10 }};
  // named variable
  Counter c{5};
  std::thread t2{c};
  t1.join();  
  t2.join();
}
