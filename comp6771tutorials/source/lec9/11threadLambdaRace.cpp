#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

// NOTE: do not compile this with -O2 it optimises out the ++ call
// and prevents the race condition from happening. 

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  // TODO: how do we fix this race condition?
  int i{0};
  const long numIterations{10000000};
  std::thread t1{[&] {
    for (int j = 0; j < numIterations; ++j) {
      i++;
    }
  }};
  std::thread t2{[&] {
    for (int j = 0; j < numIterations; ++j) {
      i--;
    }
  }};
  t1.join();  
  // TODO: what happens if we comment out t2.join()
  t2.join();

  auto end = std::chrono::high_resolution_clock::now();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "got " << i << ", took " << millis.count() << " milliseconds\n";
}
