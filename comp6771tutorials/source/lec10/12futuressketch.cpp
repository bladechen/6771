#include <chrono>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <type_traits>
#include <vector>

template <typename RAIter>
auto divide_work(RAIter begin, RAIter end, unsigned n) {
  std::vector<RAIter> work{begin};

  auto len = std::distance(begin, end);
  auto singlework = len / n;
  auto extra = len % n;
  for (auto i = 0U; i < n; ++i)
    work.push_back(work.back() + singlework + (i < extra ? 1 : 0));
  return work;
}

template <typename RAIter>
long long parallel_sum(RAIter begin, RAIter end) {
  auto work = divide_work(begin, end, std::thread::hardware_concurrency());

  std::vector<std::future<long long>> vec;
  const auto calc = [] (auto begin, auto end) {
    return std::accumulate(begin, end, 0LL);
  };
  for (auto i = 0U; i < work.size() - 1; ++i)
    vec.push_back(std::async(std::launch::async, calc, work[i], work[i + 1]));

  return std::accumulate(vec.begin(), vec.end(), 0LL, [] (auto& n, auto& fut) { return n + fut.get(); });
}



int main() {
  std::vector<int> v;
  for (auto i = 0U; i < 10000000; ++i)
    v.push_back(i);

  auto start = std::chrono::high_resolution_clock::now();
  for (auto i = 0; i < 100; ++i)
    parallel_sum(v.begin(), v.end());

  auto end = std::chrono::high_resolution_clock::now();
  auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "Parallel took " << millis.count() << "ms\n";

  auto start2 = std::chrono::high_resolution_clock::now();
  for (auto i = 0; i < 100; ++i)
    std::accumulate(v.begin(), v.end(), 0LL);

  auto end2 = std::chrono::high_resolution_clock::now();
  auto millis2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
  std::cout << "Sequential took " << millis2.count() << "ms\n";
}
