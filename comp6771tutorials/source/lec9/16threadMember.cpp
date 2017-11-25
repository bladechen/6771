#include <functional>
#include <iostream>
#include <thread>

struct Iterator {
  void counter(int numIterations) {
    for (int i = 0; i < numIterations; ++i) {
      std::cout << "Thread id: " << std::this_thread::get_id();
      std::cout << " value = " << i << std::endl;
    }
  }
};

int main() {
  Iterator i; // create an object
  // call the member function through a thread
  // a member function is just like any other function
  // TODO: explain constness here
  std::function<void(Iterator*, int)> f = &Iterator::counter;
  std::thread t1 { &Iterator::counter, &i, 10 };
  // call the same member function on the same object in parallel
  i.counter(5);
  t1.join();  
}
