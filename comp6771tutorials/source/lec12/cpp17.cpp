#include <iostream>
#include <mutex>
#include <optional>
#include <utility>
#include <vector>

int main() {
  std::cout << std::boolalpha;
  // NOTE: YOU NEED G++-7 FOR THIS

  // thanks to class template argument deduction we don't need the make_x functions anymore
  //
  // make_unique and make_shared are exceptions as they do something different. Why do we still need them?
  std::pair p{3, 4.5};

  // no longer need exceptions
  static_assert(true);
  std::cout << "Fail";

  std::vector shared_data{1, 2, 3};

  std::mutex m;
  // what's the issue with this, and how can we solve this with c++17
  if (std::lock_guard<std::mutex> lk{m}; !shared_data.empty()) {
    // do something with back
    shared_data.pop_back();
  } else {
    shared_data.push_back(5);
  }

  // How would we do this in C++14? What is better about this method than c++14
  std::optional<int> optint = 5;
  if (optint) {
    std::cout << *optint << '\n';
  }

  // also see https://ericniebler.github.io/range-v3/
  //
}
