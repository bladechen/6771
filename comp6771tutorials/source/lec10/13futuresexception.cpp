#include <iostream>
#include <future>
#include <thread>
#include <chrono>

int calculate() {
  throw std::runtime_error("Exception thrown from thread");
}

int main() {

  std::future<int> fut = std::async(std::launch::async,calculate);
  
  bool doOtherWork = true;
  while (doOtherWork) {
    // check if the result is available. 
    if (fut.wait_for(std::chrono::seconds(0)) == std::future_status::timeout) {
      // do other work.. e.g. go to a different factory.
    } else {
      // either the result is available or the launch has been deferred
      doOtherWork = false;
    }
  }
  
  try {
    int res = fut.get(); // get the result from the future
    std::cout << res << std::endl;
  } catch (const std::exception& ex) {
    std::cout << "Exception caught" << std::endl;
  }
}
