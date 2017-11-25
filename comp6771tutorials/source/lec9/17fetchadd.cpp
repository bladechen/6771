#include <iostream>
#include <atomic>
#include <thread>

int main() {
  std::atomic<int> i{10};
  std::cout << "Initial Value: " << i << std::endl;
  int fetchedValue = i.fetch_add(5);
  std::cout << "Fetched Value: " << fetchedValue << std::endl;
  std::cout << "Current Value: " << i << std::endl;
}
