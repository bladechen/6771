#include <algorithm>
#include <chrono>
#include <exception>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <mutex>
#include <string>
#include <thread>

using namespace std::experimental;

int main(int argc, char** argv) {
  std::mutex m;

  if (argc < 3)
    throw std::invalid_argument{"Must provide 3 arguments"};

  const std::string path = argv[1];
  const std::string search = argv[2];
  // note: this is actually C++17, but I'm using it as an example

  std::vector<std::pair<long, filesystem::directory_entry>> results;
  std::vector<std::thread> threads;

  auto start = std::chrono::high_resolution_clock::now();
  
  for (const auto& f : filesystem::recursive_directory_iterator{path}) {
    if (filesystem::is_regular_file(f)) {
      threads.emplace_back([f, &search, &results, &m] () {
        std::ifstream fin(f.path());
        auto matches = std::count(std::istream_iterator<std::string>(fin), std::istream_iterator<std::string>(), search);
        std::lock_guard<std::mutex> lg{m};
        results.emplace_back(matches, f);
      });
    }
  }

  for (auto& thread : threads) {
    thread.join();
  }

  std::sort(results.begin(), results.end());

  for (const auto& pair : results)
    std::cout << search << " appears " << pair.first << " times in " << pair.second << '\n';
  auto end = std::chrono::high_resolution_clock::now();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Took " << millis.count() << '\n';
}
