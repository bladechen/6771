#include<iostream>
#include<typeinfo>

void e(const int&, int, int) {
  std::cout << "1\n";
}

void e(int&, int, int) {
  std::cout << "2\n";
}

template <typename A, typename B, typename C>
void f(A &&a, B &&b, C &&c) {
  // always call std::forward, never forward
  e(std::forward<A>(a), std::forward<B>(b), std::forward<C>(c));
}

int k{1};
int g() { return k; }

int main() {
  f(1,2,3);
  int i{1};
  f(i,2,3);
  const int &j = i;
  f(j,2,3);
  f(g(),2,3);
}
