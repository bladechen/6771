#include <exception>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
  int i = 0;
  const long numIterations = 1000000;
  std::mutex iMutex;
  std::thread t1([&] {
    for (int j = 0; j < numIterations; ++j) {
      std::lock_guard<std::mutex> lg{iMutex};
      i++;
    }
  });
  std::thread t2([&] {
    int k;
    for (int j = 0; j < numIterations; ++j) {
      {
        std::lock_guard<std::mutex> lg{iMutex};
        i--;
      }
      k++;
    }
  });
  t1.join();
  t2.join();
  std::cout << i << std::endl;
}
