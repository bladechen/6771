#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

template <typename T>
struct remove_reference {
  using type = T;
};

template <typename T>
struct remove_reference<T&> {
  using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T>
struct is_numeric {
  constexpr operator bool() {
    return value;
  }

  static const bool value = false;
};

template <>
struct is_numeric<int> {
  static const bool value = true;
};

template <>
struct is_numeric<const int> {
  constexpr operator bool() {
    return value;
  }
  static const bool value = true;
};

template <typename U>
auto findmin(U begin, U end) {
  using T = remove_reference_t<decltype(*begin)>;
  static_assert(is_numeric<T>(), "Value must be numeric");
  auto min = std::numeric_limits<T>::max();
  for (; begin != end; ++begin)
    min = std::min(*begin, min); // this is why you don't go using namespace std
  return min;
}

int main() {
  std::cout << std::numeric_limits<int>::min() << '\n';
  std::cout << std::numeric_limits<int>::max() << '\n';

  std::vector<int> vi{5, 1, 2, 3, 7, 4};
  std::vector<int> vempty;
  std::vector<std::string> vs{"hello", "world"};
  
  // also see std::min_element
  std::cout << "min of vi is " << findmin(vi.cbegin(), vi.cend()) << '\n';
  std::cout << "min of vempty is " << findmin(vempty.cbegin(), vempty.cend()) << '\n';

  // this clearly doesn't work the way we want it to. How can we use type traits to ensure this template only works for numbers?
  // std::cout << "min of vs is " << findmin(vs.cbegin(), vs.cend()) << '\n';
}
