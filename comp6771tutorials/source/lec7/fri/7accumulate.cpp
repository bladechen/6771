#include <iostream>

template <template <unsigned n, unsigned m> class Functor, template <unsigned n> class Map, unsigned n>
struct Accumulate {
  static const unsigned val = Functor<Map<n>::val, Accumulate<Functor, Map, n - 1>::val>>;
};

template <>
struct Accumulate<template <unsigned n, unsigned m> class Functor, template <unsigned n> class Map, 1> {
  static const unsigned val = Map<1>::val
};

template <unsigned n>
struct Identity {
  static const unsigned val = n;
};

template <unsigned n>
struct Square {
  static const unsigned val = n * n;
};

template <unsigned n, unsigned m>
struct Plus {
  static const unsigned val = n + m;
};

template <unsigned n, unsigned m>
struct Times {
  static const unsigned val = n * m;
};


int main() {
  
  std::cout << Accumulate<Plus, Identity, 4>::val << '\n';
  std::cout << Accumulate<Times, Identity, 4>::val << '\n';
  std::cout << Accumulate<Plus, Square, 4>::val << '\n';
  std::cout << Accumulate<Times, Square, 4>::val << '\n';
  
}
