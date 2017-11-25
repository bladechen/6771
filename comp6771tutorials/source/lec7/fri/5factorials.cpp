#include <iostream>

template <unsigned n>
struct Factorial {
  static const unsigned val = n * Factorial<n - 1>::val;
};

template<>
struct Factorial<0> {
  static const unsigned val = 1;
};

constexpr unsigned factorial(unsigned n) {
  if (n == 0)
    return 1;
  return n * factorial(n - 1);
}

int main() {
  std::cout << factorial(10) << '\n';
  std::cout << Factorial<10>::val << '\n';
}
