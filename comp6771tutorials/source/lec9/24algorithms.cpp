#include <iterator>
#include <thread>
#include <vector>
#include <iostream>
#include <cassert>
#include <cmath>


template<class ForwardIt, class UnaryFunction>
void for_each(ForwardIt first, ForwardIt last, UnaryFunction f, unsigned ncores) {
  auto n = std::distance(first, last);
  auto each = n / ncores;
  auto nbonus = n % ncores;

  std::vector<std::thread> threads;

  for (auto i = 0U; i < ncores; ++i) {
    auto last = std::next(first, each + (i < nbonus ? 1 : 0));
    threads.emplace_back([first, last, &f] () {
      for (auto s = first; s != last; ++s) {
        f(*s);
      }
    });
    first = last;
  }

  for (auto& thread : threads)
    thread.join();
  assert(first == last);
}

template<class ForwardIt, class UnaryFunction>
void for_each(ForwardIt first, ForwardIt last, UnaryFunction f) {
    return for_each(first, last, f, std::thread::hardware_concurrency());
}

// 0 and 1 are prime according to this definition. Convenient for us because it works with the closest_prime_leq function
bool is_prime(unsigned n) {
    for (auto i = 2U; i <= std::sqrt(n); ++i)
        if (n % i == 0)
            return false;
    return true;
}

void closest_prime_leq(unsigned& n) {
    while (!is_prime(n))
        --n;
}

int main() {
    std::vector<int> n(100000, 10);
    for_each(n.begin(), n.end(), [] (auto) {}, 3);
    for_each(n.begin(), n.end(), [] (auto) {}, 4);
    for_each(n.begin(), n.end(), [] (auto) {}, 5);

    std::vector<int> n2(1, 5);
    for_each(n2.begin(), n2.end(), [] (auto) {}, 5);

    std::vector<unsigned> primes;
    for (auto i = 0U; i < 1000000; ++i)
        primes.push_back(i);
    auto start = std::chrono::high_resolution_clock::now();
    for_each(primes.begin(), primes.end(), closest_prime_leq);
    auto end = std::chrono::high_resolution_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    // careful: some things cannot be done concurrently
    for_each(primes.begin(), primes.begin() + 50, [] (auto n) { std::cout << n << '\n'; }, 1);
    std::cout << "took " << millis.count() << " milliseconds\n";
}
